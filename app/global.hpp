#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <functional>
#include <iostream>

#include "global.hpp"

namespace Resources
{
    sf::ContextSettings settings;
    sf::Vector2u window_size;
    sf::RenderWindow window;
    sf::SoundBuffer buffer;
    sf::Font font;
    sf::Text debugText;

    bool load_resourses()
    {
        // loading sound
        if (!buffer.loadFromFile("Assets/Audio/beep.wav"))
            return false;

        // loading font
        if (!font.loadFromFile("Assets/Fonts/roboto.ttf"))
            return false;

        return true;
    }

    void start()
    {
        window_size = sf::Vector2u(1000, 720);
        settings.antialiasingLevel = 16;
        window.create(sf::VideoMode(window_size.x, window_size.y), "Gem Puzzle", sf::Style::Close, settings);
        window.setFramerateLimit(30);

        load_resourses();

        debugText.setFont(font);
        debugText.setCharacterSize(20);
        debugText.setFillColor(sf::Color::Cyan);
    }
    
    void setDebugText(std::string s)
    {
        debugText.setString(s);
        debugText.setPosition(5, window_size.y - debugText.getGlobalBounds().height-10);
    }
    
    void appendDebugText(std::string s){
        debugText.setString(debugText.getString()+"\n"+s);
        debugText.setPosition(5, window_size.y - debugText.getGlobalBounds().height-10);
    }

    sf::Vector2i mousePosition() { return sf::Mouse::getPosition(window); }
}

#endif // GLOBAL_H