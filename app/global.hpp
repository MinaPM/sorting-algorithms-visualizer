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

    struct Padding
    {
        int top = 10, left = 10, right = -10, bottom = -10;

    } padding;

    sf::ContextSettings settings;
    sf::Vector2u window_size;
    sf::RenderWindow window;
    sf::SoundBuffer buffer;
    sf::Font font;
    sf::Text debugText;
    int characterSize;
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

    void initialize()
    {
        window_size = sf::Vector2u(1000, 720);
        settings.antialiasingLevel = 16;
        window.create(sf::VideoMode(window_size.x, window_size.y), "Gem Puzzle", sf::Style::Close, settings);
        window.setFramerateLimit(30);
        characterSize = 20;
        load_resourses();

        debugText.setFont(font);
        debugText.setCharacterSize(characterSize);
        debugText.setFillColor(sf::Color::Cyan);
    }

    void setDebugText(std::string s)
    {
        debugText.setString(s);
        debugText.setPosition(5, window_size.y - debugText.getGlobalBounds().height +padding.bottom);
    }

    void appendDebugText(std::string s)
    {
        debugText.setString(debugText.getString() + "\n" + s);
        debugText.setPosition(5, window_size.y - debugText.getGlobalBounds().height + padding.bottom);
    }

    sf::Vector2i mousePosition() { return sf::Mouse::getPosition(window); }
}

#endif // GLOBAL_H