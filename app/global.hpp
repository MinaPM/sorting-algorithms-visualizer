#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <functional>
#include <iostream>
#include <random>
#include <map>

#include "smartArray.hpp"
#include "Algorithms/algorithm.hpp"
#include "Algorithms/insertionSort.hpp"
#include "Algorithms/mergeSort.hpp"
#include "Bar/BarShape.h"

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
    sf::Text debugText(font);
    int characterSize;
    bool load_resourses()
    {
        // loading sound
        if (!buffer.loadFromFile("assets/audio/beep.wav"))
            return false;

        // loading font
        if (!font.openFromFile("assets/fonts/roboto.ttf"))
            return false;

        return true;
    }

    void initialize()
    {
        window_size = sf::Vector2u(1500, 900);
        settings.antiAliasingLevel = 0;
        window.create(sf::VideoMode(window_size), "Sorting Algorithm Visualizer", sf::Style::Close /*, settings*/);
        window.setFramerateLimit(30);
        characterSize = 20;
        load_resourses();

        debugText.setFont(font);
        debugText.setCharacterSize(characterSize);
        debugText.setFillColor(sf::Color::Red);
        debugText.setOutlineColor(sf::Color::Black);
        debugText.setOutlineThickness(5);
    }

    void setDebugText(std::string s)
    {
        debugText.setString(s);
        debugText.setPosition({window_size.x - debugText.getGlobalBounds().size.x + padding.right, window_size.y - debugText.getGlobalBounds().size.y + padding.bottom * 2});
    }

    void appendDebugText(std::string s)
    {
        setDebugText(debugText.getString() + "\n" + s);
    }

    sf::Vector2i mousePosition() { return sf::Mouse::getPosition(window); }

    //close event
    const auto onClose = [](const sf::Event::Closed&)
    {
       window.close();
    };
}


namespace GlobalVars
{
    SmartArray<BarShape> bars;
    Algorithm *sortingAlgorithm;
    InsertionSort insersion(bars);
    MergeSort mergeSort(bars);

}


#endif // GLOBAL_H