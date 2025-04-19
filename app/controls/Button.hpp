#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Control.hpp"

class Button : public Control<void>
{
public:
    std::thread buttonThread;
    
    Button(const std::string &text) : Control(text)
    {
        rectangle.setSize(sf::Vector2f(lable.getLocalBounds().width + 10,
                                       lable.getLocalBounds().height + 10));
        setPosition(0, 0);
        setColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
    }

    void setPosition(float x, float y)
    {
        rectangle.setPosition(x, y);
        lable.setPosition(rectangle.getPosition());
    }

    void click()
    {
        if (!enabled || onTrigger == nullptr)
            return;
        if (buttonThread.joinable())
        buttonThread.join();

        buttonThread = std::thread(&Button::run, this);
    }

private:
    void run()
    {
        disable();
        if (onTrigger)
            onTrigger();
        enable();
    }
};

#endif // BUTTON_HPP
