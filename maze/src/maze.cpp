#include <iostream>
#include "maze.h"

Maze::Maze()
{
    _height = 0;
    _width  = 0;
    _maze   = nullptr;
}

Maze::~Maze()
{
    clearMaze();
}

void Maze::clearMaze()
{
    if (_maze != nullptr)
    {
        for (int i = 0; i < _height; ++i)
        {
            if (_maze[i] != nullptr)
                delete[] _maze[i];
        }
        delete[] _maze;
    }
}

int** Maze::generateMaze(int &height, int &width)
{
    srand(time(NULL));
    _height = height;
    _width  = width;
    height  = height * 2 + 1;
    width   = width  * 2 + 1;

    clearMaze();
    createMaze();
    generateMazeMap(rand() % _width, rand() % _height);

    int **final_map = createMap(height, width);
    return convertMazeToMap(final_map, height, width);
}

static std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void Maze::generateMazeMap(int x, int y)
{
    int direct = rand() % directions.size();
    _maze[y][x].visited = true;
    for (int i = 0; i < directions.size(); ++i)
    {
        int offset = (direct + i) % directions.size();
        int dx = directions[offset].first  + x;
        int dy = directions[offset].second + y;
        if (dx >= 0  && dx < _width)
        {   
            if (dy >= 0  && dy < _height)
            {
                if (!_maze[dy][dx].visited)
                {
                    //delete wall
                    switch (offset)
                    {
                    case 0:
                        _maze[dy][dx].left = false;
                        break;
                    case 1:
                        _maze[y][x].bottom = false;
                        break;
                    case 2:
                        _maze[y][x].left = false;
                        break;
                    case 3:
                        _maze[dy][dx].bottom = false;
                        break;
                    }

                    generateMazeMap(dx, dy);
                }
            }
        }
    }
}

int** Maze::createMap(int &height, int &width)
{
    int **map = new int*[height];
    for (int i = 0; i < height; ++i)
        map[i] = new int[width];
    return map;
}

void Maze::createMaze()
{
    if (_maze != nullptr)
        clearMaze();

    _maze = new Maze::maze_cell*[_height];
    for (int i = 0; i < _height; ++i)
    {
        _maze[i] = new Maze::maze_cell[_width];
        for (int j = 0; j < _width; ++j)
            _maze[i][j] = {true, true, false};
    }
}

int** Maze::convertMazeToMap(int** final_map, int height, int width)
{
    if (final_map == nullptr || _maze == nullptr) 
        return nullptr;

    for (int i = 0; i < height; ++i)
        final_map[i][width - 1] = wall;
    for (int i = 0; i < width; ++i)
        final_map[0][i] = wall;

    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            int cell = wall;
            if (_maze[i][j].left == false) 
                cell = space;
            final_map[i * 2 + 1][j * 2] = cell;

            cell = wall;
            if (_maze[i][j].bottom == false) 
                cell = space;
            final_map[i * 2 + 2][j * 2 + 1] = cell;

            final_map[i * 2 + 1][j * 2 + 1] = space;
            final_map[i * 2 + 2][j * 2]     = wall;
        }
    }

    return final_map;
}
