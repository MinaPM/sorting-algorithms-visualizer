// #include "global.hpp"

// namespace Resources
// {
//     sf::ContextSettings settings;
//     sf::Vector2u window_size;
//     sf::RenderWindow window;
//     sf::SoundBuffer buffer;
//     sf::Font font;

//     void start()
//     {
//         window_size = sf::Vector2u(1000, 720);
//         settings.antialiasingLevel = 16;
//         window.create(sf::VideoMode(window_size.x, window_size.y), "Gem Puzzle", sf::Style::Close, settings);
//         window.setFramerateLimit(30);

//         load_resourses();
//     }

//     bool load_resourses()
//     {
//         // loading sound
//         if (!buffer.loadFromFile("Assets/Audio/beep.wav"))
//             return false;

//         // loading font
//         if (!font.loadFromFile("Assets/Fonts/roboto.ttf"))
//             return false;

//         return true;
//     }

//     sf::Vector2i mousePosition() { return sf::Mouse::getPosition(window); }
// }