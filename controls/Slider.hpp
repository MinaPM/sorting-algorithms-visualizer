#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "Control.hpp"

class Slider : public Control<int>
{
protected:

    void setLayout() override
    {

        int x=label.getX()+label.getSize().w + 10;
        int y=label.getY() + label.getSize().h;
        rectangle.setPosition(x, y);
        
        current_rect.setPosition(rectangle.getPosition());
        
        current_text.setPosition(rectangle.getPosition());
        current_text.setX(current_text.getX() + (width +5));
        
        // rectangle.setPosition(50, 50);
        // current_rect.setPosition(rectangle.getPosition());
        // current_text.setPosition(rectangle.getPosition());
        
    }

public:
    Text current_text;
    Rectangle current_rect;
    int min, max, width;

    Slider() : Control()
    {
    }

    Slider(const std::string& text, int min, int current, int max) : Control(text)
    {
        width = 100;
        this->min = min;
        this->max = max;
        this->controlable = current;
        current_text.setText(std::to_string(current));

        rectangle.setSize(width, 20);
        current_rect.setSize(((current - min) / (max - min)) * width, 20);

        // setColor(SDL_Color{255, 255, 255}, SDL_Color{255, 0, 0}, SDL_Color{255, 255, 255});
        setLayout();
    }

    // void setPosition(sf::Vector2f position) override{}
    void setPosition(float x, float y)
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

        SDL_Point point = Resources::mousePosition();
        //come here later
        int length = std::max(0, std::min(width, point.x - current_rect.getX()));
        controlable = (length / width) * (max - min) + min;
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

    void draw(SDL_Renderer* renderer) 
    {
        Control::draw(renderer);
        current_rect.draw(renderer);
        current_text.draw(renderer);
    }

    // void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
    // {
    //     Control::draw(rt, states);
    //     states.transform *= getTransform();
    //     rt.draw(current_rect, states);
    //     rt.draw(current_text, states);
    // }
};

#endif // SLIDER_HPP
