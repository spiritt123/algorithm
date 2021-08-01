#pragma once


#include <climits>
#include <cmath>
#include <list>
#include <SFML/Graphics.hpp>
#include "enums.h"

class Maze
{
public:
    Maze();
    int** generateMaze(int &height, int &width);
    ~Maze();
    
    struct maze_cell
    {
        bool left;
        bool bottom;
        bool visited;
    }; 

private:
    int _width;
    int _height;
    maze_cell **_maze;

private:
    void clearMaze();
    void generateMazeMap(int x, int y);
    
    int** createMap(int &height, int &width);
    void createMaze();

    int** convertMazeToMap(int** final_map, int height, int width);
};

