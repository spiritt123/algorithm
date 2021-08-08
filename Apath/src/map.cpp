#include "map.h"


Map::point::point(){}
Map::point::~point(){}
Map::point::point(int X, int Y){x = X; y = Y;}

Map::Map()
{
    _height = 0;
    _width  = 0;
    _xmap   = nullptr;
}

Map::~Map()
{
    clear_map();
}

void Map::addNewPath(int **map, int height, int width, int x1, int y1, int x2, int y2)
{
    _height = height;
    _width  = width;

    convertMapToXmap(map);
    applyPathToMap(createPath(point(x1, y1), point(x2, y2)), map);
}

void Map::clear_map()
{
    if (_xmap != nullptr)
    {
        for (int i = 0; i < _height; ++i)
        {
            if (_xmap[i] != nullptr)
                delete[] _xmap[i];
        }
        delete[] _xmap;
    }
}

void Map::convertMapToXmap(int **map)
{
    clear_map();
    
    _xmap = new xmap_cell*[_height];
    for (int i = 0; i < _height; ++i)
    {
        _xmap[i] = new xmap_cell[_width];
        for (int j = 0; j < _width; ++j)
        {
            _xmap[i][j] = {map[i][j], 0, INT_MAX / 2, false, point(j, i), point(j, i)};
        }
    }
}

int Map::distant(point start, point end)
{
    point distant = point((end.x - start.x), (end.y - start.y));
    return (int)sqrt(distant.x * distant.x + distant.y * distant.y);
}

void Map::findNewNeighbour(std::list<Map::xmap_cell> &active_cells, point target)
{
    Map::xmap_cell cell = active_cells.front();
    cell.visited = true;
    point center = cell.position;
    point lt = center, rb = center;
    if (lt.x != 0) --lt.x;
    if (lt.y != 0) --lt.y;
    if (rb.x != _width - 1) ++rb.x;
    if (rb.y != _height - 1) ++rb.y;
    int distant_to_start = _xmap[center.y][center.x].distant_to_start;
    int addit_distant[2] = {10, 14};
    int k = 0;
    for (int i = lt.y; i <= rb.y; ++i)
    {
        for (int j = lt.x; j <= rb.x; ++j)
        {
            k ^= 1;
            
            if (i == center.y && j == center.x) continue;
            if (_xmap[i][j].value == wall) continue;
            
            int sum = distant_to_start + addit_distant[k] + distant(_xmap[i][j].position, target) * 10;
            if (_xmap[i][j].visited == true)
            {
                if (sum >= _xmap[i][j].sum)
                {
                    continue;
                }
                else
                {
                    for (auto &cell : active_cells)
                    {
                        if (cell.position == _xmap[i][j].position)
                        {
                            cell.distant_to_start = distant_to_start + addit_distant[k];
                            cell.sum = sum;
                            cell.source = center;
                            continue; 
                        }
                    }
                }
            } 

            _xmap[i][j].distant_to_start = distant_to_start + addit_distant[k];
            _xmap[i][j].sum = sum;
            _xmap[i][j].source = center;
            _xmap[i][j].visited = true;

            active_cells.push_back(_xmap[i][j]);
        }
    }
}
 
std::list<Map::point> Map::createPath(point start, point target)
{
    std::list<point> path;

    std::list<xmap_cell> active_cells;
    active_cells.push_back(_xmap[start.y][start.x]);
    
    _xmap[start.y][start.x].distant_to_start = 0;
    _xmap[start.y][start.x].sum = distant(_xmap[start.y][start.x].position, target);
    _xmap[start.y][start.x].visited = true;

    while (_xmap[target.y][target.x].visited != true)
    {
        active_cells.sort([](const xmap_cell &a, const xmap_cell &b)
                            { return a.sum < b.sum;} );
        findNewNeighbour(active_cells, target);
        active_cells.erase(active_cells.begin());
    }

    while (distant(start, target) > 1 )
    {
        path.push_back(target = _xmap[target.y][target.x].source);
    }
    return path;
}

void Map::applyPathToMap(std::list<point> path_vectors, int **map)
{
    for (auto cell : path_vectors)
    {
        map[cell.y][cell.x] = path;
    }
}


