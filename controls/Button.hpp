#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Control.hpp"

class Button : public Control<int>
{
protected:
    void setLayout() override
    {
        int topPadding = (rectangle.getSize().y - label.getSize().y) / 2;
        int leftPadding = (rectangle.getSize().x - label.getSize().x) / 2;
        label.setPosition(rectangle.getPosition().x + leftPadding,
                          rectangle.getPosition().y + topPadding);
    }

public:
    Button(Button &&) noexcept = default; // Move constructor

    Button()
    {
        setColor(Colors::WHITE, Colors::OUTLINE, Colors::MAIN);
    }

    Button(const std::string &text) : Button()
    {
        setString(text);
    }

    void setPosition(float x, float y)
    {
        rectangle.setPosition(x, y);
        setLayout();
    }

    void setString(const std::string &text)
    {
        label.setText(text);
        rectangle.setSize(label.getSize().x + 7, label.getSize().y + 5);
        setLayout();
    }

    void click()
    {
        if (!enabled || !onTrigger)
            return;

#ifdef __EMSCRIPTEN__
        run();
#else
        if (buttonThread.joinable())
            buttonThread.join();

        buttonThread = std::thread(&Button::run, this);
#endif
    }

    ~Button()
    {
#ifndef __EMSCRIPTEN__
        if (buttonThread.joinable())
            buttonThread.join();
#endif
    }

private:
#ifndef __EMSCRIPTEN__
    std::thread buttonThread;
#endif

    void run()
    {
        disable();
        if (onTrigger)
            onTrigger();
        enable();
    }
};

#endif // BUTTON_HPP
