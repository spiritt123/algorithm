#include <iostream>
#include <SFML/Graphics.hpp>
#include "maze.h"
#include "enums.h"

void show(int** map, int height, int width);

int main(int argc, char* argv[])
{
    Maze maze;

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);;
    int **place = maze.generateMaze(height, width);

    show(place, height, width);

    return 0;
}

void show(int** map, int height, int width)
{
    if (map == nullptr)
    {
        std::cerr << "is't map\n";
        return;
    }

    int size_cell = 40;
    sf::RenderWindow window(sf::VideoMode(width * size_cell, height * size_cell), "Maze");
    window.setFramerateLimit(30);

    std::map <int, sf::Color> table_colors = 
    {
        {space,  sf::Color::White},
        {wall,   sf::Color::Black},
    };
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();             
            }
        }

        window.clear();

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(size_cell, size_cell));
                rectangle.setFillColor(table_colors[map[i][j]]);
                rectangle.setOutlineColor(sf::Color::Black);
                rectangle.setOutlineThickness(2);
                rectangle.setPosition(j * size_cell, i * size_cell);
                window.draw(rectangle);
            }
        }

        window.display();
    }

}

