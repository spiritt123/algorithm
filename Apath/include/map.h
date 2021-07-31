#pragma once


#include <climits>
#include <cmath>
#include <list>
#include <SFML/Graphics.hpp>
#include "enums.h"

class Map
{
public:
    Map();
    void addNewPath(int **map, int height, int width, int x1, int y1, int x2, int y2);
    ~Map();
    
    class point
    {
    public:
        point();
        point(int X, int Y);
        ~point();
        int x, y;
    };

    struct xmap_cell
    {
        int value;
        int distant_to_start;
        int sum;
        bool visited;
        point position;
        point source;
    }; 

private:
    int _width;
    int _height;
    xmap_cell **_xmap;

private:
    void clear_map();
    int distant(point start, point end);

    void convertMapToXmap(int **map);
    
    std::list<xmap_cell> findNewNeighbour(xmap_cell cell, point target);
    
    std::list<point> createPath(point start, point target);
    
    void applyPathToMap(std::list<point> path_vectors, int **map);
};

