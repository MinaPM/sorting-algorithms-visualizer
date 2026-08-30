#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "Control.hpp"

class Slider : public Control<int>
{
protected:
    void setLayout() override
    {

        int x = label.getX();// + label.getSize().x + 10;
        int y = label.getY() + label.getSize().y+rectangle.getHeight();
        rectangle.setPosition(x, y);

        current_rect.setPosition(x, y);

        current_text.setPosition(rectangle.getPosition());
        current_text.setX(current_text.getX() + (width + 5));
    }

public:
    Text current_text;
    Rectangle current_rect;
    int min, max, width;

    Slider() : Control()
    {
    }

    Slider(const std::string &text, int min, int current, int max) : Control(text)
    {
        width = 100;
        this->min = min;
        this->max = max;

        this->controlable = current;
        current_text.setText(std::to_string(current));

        rectangle.setSize(width, 20);
        current_rect.setSize(((float)(current - min) / (max - min)) * width, 20);

        setColor(Colors::WHITE, Colors::RED, Colors::WHITE);
        setLayout();
    }

    void setPosition(int x, int y)
    {
        label.setPosition(x, y);
        setLayout();
    }

    void setMinMax(int min, int max)
    {
        this->min = min;
        this->max = max;
        setValue();
    }

    void setValue()
    {
        if (!enabled || !clicked)
            return;

        SDL_Point mouseP = Resources::mousePosition();
        int length = std::max(0, std::min(width, mouseP.x - current_rect.getX()));
        controlable = (length / (float)width) * (max - min) + min;
        update();
        // a feedback to limit the slider in other places using a pointer to controlable
        length = width * (controlable - min) / (max - min);
        current_rect.setSize(length, current_rect.getHeight());
        current_text.setText(std::to_string(controlable));
    }

    int getPercentage() { return 100 * (max - controlable); }

    void enable()
    {
        Control::enable();
        setColor(rectangle.getFillColor(), rectangle.getOutlineColor(), label.getColor());
    }

    void disable()
    {
        Control::disable();
        setColor(rectangle.getFillColor(), rectangle.getOutlineColor(), label.getColor());
    }

    void setColor(SDL_Color fill, SDL_Color outline, SDL_Color text)
    {
        Control::setColor(fill, outline, text);
        current_rect.setFillColor(outline);
        current_text.setColor(text);
    }

    void draw(SDL_Renderer *renderer)
    {
        Control::draw(renderer);
        current_rect.draw(renderer);
        current_text.draw(renderer);
        // getBoundingRect().draw(renderer);
    }
    
    Rectangle getBoundingRect()
    {
        return Control::getBoundingRect() + current_rect + current_text.getSDLRect();
    }
};

#endif // SLIDER_HPP
