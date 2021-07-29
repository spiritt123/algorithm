#include <iostream>

#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <SFML/Graphics.hpp>



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");


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
        
        //window.draw(shape);
        window.display();
    }

    return 0;
}




