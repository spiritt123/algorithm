#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "enums.h"

const int size_cell = 40;


void show(sf::RenderWindow &window, int** map, int height, int width);
void clearAllPath(int **place, int height, int width);
void show_manual();

int main()
{
    const int width  = 40;
    const int height = 20;
    sf::RenderWindow window(sf::VideoMode(width * size_cell, height * size_cell), "Press H for insormation");
    window.setFramerateLimit(30);
    
    int **place = new int*[height];
    for (int i = 0; i < height; place[i++] = (int *)calloc(width, sizeof(int)));

    Map map;

    int status_button = clear;

    std::vector<sf::Vector2i> start_vectors, target_vectors;

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
                if (event.key.code == sf::Keyboard::P)
                {
                    clearAllPath(place, height, width);
                    for (auto start_vector : start_vectors)
                        for (auto target_vector : target_vectors)
                            map.addNewPath(place, height, width, start_vector.x, start_vector.y, target_vector.x, target_vector.y);
                }
                
                if (event.key.code == sf::Keyboard::C) status_button = clear;
                if (event.key.code == sf::Keyboard::W) status_button = wall;
                if (event.key.code == sf::Keyboard::T) status_button = target;
                if (event.key.code == sf::Keyboard::S) status_button = start;
                if (event.key.code == sf::Keyboard::H) show_manual();
                
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                position = sf::Vector2i(position.x / size_cell, position.y / size_cell);
                if (status_button == target) target_vectors.push_back(position);
                if (status_button == start)  start_vectors.push_back(position);
                if (status_button == clear)
                {
                    if (place[position.y][position.x] == start) 
                    {
                        start_vectors.erase(
                                std::remove(start_vectors.begin(), 
                                            start_vectors.end(), 
                                            position), 
                                start_vectors.end()
                        );
                        std::cout << start_vectors.size() << "\n";
                    }
                    if (place[position.y][position.x] == target)
                        target_vectors.erase(
                                std::remove(target_vectors.begin(), 
                                            target_vectors.end(), 
                                            position), 
                                target_vectors.end()
                        );
                }
                place[position.y][position.x] = status_button;
            }

        }

        window.clear();
        show(window, place, height, width);
        window.display();
    }

    for (int i = 0; i < height; ++i)
        delete[] place[i];
    delete[] place;
    return 0;
}

void show(sf::RenderWindow &window, int** map, int height, int width)
{
    std::map <int, sf::Color> table_colors = 
    {
        {clear,  sf::Color::White},
        {start,  sf::Color::Red},
        {target, sf::Color::Blue},
        {path,   sf::Color::Green},
        {wall,   sf::Color::Yellow},
    };

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
}

void clearAllPath(int **place, int height, int width)
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (place[i][j] == path) place[i][j] = clear;
        }
    }
}

void show_manual()
{
    sf::RenderWindow window(sf::VideoMode(640, 380), "Press H for insormation");
    window.setFramerateLimit(30);

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("./font/font.ttf"))
        std::cerr << "Error, font don't loaded!!!\n"; 
    
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

        text.setFont(font); 
        text.setCharacterSize(24); 
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        std::string message;
        message += "Press the button and click mouse :)\n";
        message += "S - start\n";
        message += "T - target\n";
        message += "W - wall\n";
        message += "C - clear\n";
        message += "Esc - exit";
        text.setString(message);
        window.draw(text);
        window.display();
    }
}
