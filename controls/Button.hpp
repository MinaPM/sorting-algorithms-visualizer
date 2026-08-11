#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Control.hpp"

class Button : public Control<int>
{
protected:
    void setLayout() override
    {
        int topPadding = (rectangle.getSize().h - label.getSize().h) / 2;
        int leftPadding = (rectangle.getSize().w - label.getSize().w) / 2;
        label.setPosition(rectangle.getPosition().x + leftPadding,
                          rectangle.getPosition().y + topPadding);
    }

public:
    Button(Button &&) noexcept = default; // Move constructor

    Button()
    {
        setColor(SDL_Color{255, 255, 255, 255}, SDL_Color{255, 0, 0, 255}, SDL_Color{255, 0, 0, 255});
    }

    Button(const std::string &text) : Button()
    {
        setString(text);
    }
    // void setPosition(sf::Vector2f position) override{}

    void setPosition(float x, float y)
    {
        rectangle.setPosition(x, y);
        setLayout();
    }

    void setString(const std::string &text)
    {
        label.setText(text);
        rectangle.setSize(label.getSize().w + 7, label.getSize().h + 5);
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
