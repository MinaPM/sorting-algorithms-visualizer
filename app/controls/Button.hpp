#ifndef BUTTON_HPP
#define BUTTON_HPP


#include "Control.hpp"

class Button : public Control<void (*)()>
{
public:
    std::thread button_thread;
    // void (*onClick)();
    Button(const sf::Font &font, const std::string &text, int size) : Control(font, text, size)
    {
        rectangle.setSize(sf::Vector2f(lable.getLocalBounds().width + 10,
                                       lable.getLocalBounds().height + 10));
        setPosition(0, 0);
        setColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
        controlable = nullptr;
    }

    void setPosition(float x, float y)
    {
        rectangle.setPosition(x, y);
        lable.setPosition(rectangle.getPosition());
    }

    void click()
    {
        if (!enabled || controlable == nullptr)
            return;
        if (button_thread.joinable())
            button_thread.join();

        button_thread = std::thread(&Button::run, this);
    }
    void setOnClick(void (*func)())
    {
        controlable = func;
    }

private:
    void run()
    {
        disable();
        if (controlable)
            controlable();
        enable();
    }
};

#endif //BUTTON_HPP
