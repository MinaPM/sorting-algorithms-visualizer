#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Control.hpp"

class Button : public Control<int>
{
protected:

    void setLayout() override
    {
        label.setPosition(rectangle.getPosition());
    }

public:
    Button(Button&&) noexcept = default; // Move constructor


    Button(const std::string& text) : Control(text)
    {
        rectangle.setSize(sf::Vector2f(label.getLocalBounds().size.x + 10,
                                       label.getLocalBounds().size.y + 10));
        setLayout();
        setColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
    }
    void setPosition(sf::Vector2f position) override{}

    void setPosition(float x, float y)
    {
        rectangle.setPosition({x, y});
        setLayout();
    }

    void click()
    {
        if (!enabled || !onTrigger)
            return;
        if (buttonThread.joinable())
            buttonThread.join();

        buttonThread = std::thread(&Button::run, this);
    }


    ~Button()
    {
        if (buttonThread.joinable())
            buttonThread.join();
    }

private:
    std::thread buttonThread;

    void run()
    {
        disable();
        if (onTrigger)
            onTrigger();
        enable();
    }
};

#endif // BUTTON_HPP
