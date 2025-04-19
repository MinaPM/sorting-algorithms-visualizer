#include "./header/Button.hpp"

Button::Button(const std::string &text, int size) : Control(text, size)
{
    rectangle.setSize(sf::Vector2f(lable.getLocalBounds().width + 10,
                                   lable.getLocalBounds().height + 10));
    setPosition(0, 0);
    setColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
    controlable = nullptr;
}

void Button::setPosition(float x, float y)
{
    rectangle.setPosition(x, y);
    lable.setPosition(rectangle.getPosition());
}

void Button::click()
{
    if (!enabled || controlable == nullptr)
        return;
    if (button_thread.joinable())
        button_thread.join();

    button_thread = std::thread(&Button::run, this);
}

void Button::setOnClick(void (*func)()) { controlable = func; }

void Button::run()
{
    disable();
    if (controlable)
        controlable();
    enable();
}
