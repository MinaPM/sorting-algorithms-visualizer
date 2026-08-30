#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../src/global.hpp"
#include "../graphics/Rectangle.hpp"
#include "../graphics/Text.hpp"
template <typename Controlable>
class Control
{
public:
    Rectangle rectangle;
    Text label;
    Controlable controlable;
    std::function<void()> onTrigger;

    bool enabled, clicked;

    Control()
    {
        enabled = true;
        clicked = false;
        rectangle.setOutlineThickness(3);
        onTrigger = nullptr;
    }

    Control(const std::string &string) : Control()
    {
        label.setText(string);
    }

    void setString(const std::string &string) { label.setText(string); }

    void setColor(SDL_Color rectangleFill, SDL_Color rectangleOutline, SDL_Color text)
    {
        rectangle.setFillColor(rectangleFill);
        rectangle.setOutlineColor(rectangleOutline);
        label.setColor(text);
    }

    bool within()
    {
        SDL_Point mousePos = Resources::mousePosition();
        SDL_Rect rect = rectangle.getSDLRect();
        return SDL_PointInRect(&mousePos, &rect);
    }

    bool clickWithin() { return clicked = within(); }
    void mouseReleased() { clicked = false; }

    bool isEnabled() { return enabled; }

    void enable()
    {
        enabled = true;
    }

    void disable()
    {
        enabled = false;
    }

    Controlable *bindControlable() { return &controlable; }

    void setOnTrigger(std::function<void()> func) { onTrigger = func; }

    void update()
    {
        if (onTrigger)
            onTrigger();
    }

    void alignLeft() { label.setPosition({rectangle.getPosition().x, label.getY()}); }

    SDL_Point getPosition()
    {
        return rectangle.getPosition();
    }

    SDL_Point getSize()
    {
        return rectangle.getSize();
    }

    void draw(SDL_Renderer *renderer)
    {
        rectangle.draw(renderer);
        label.draw(renderer);
    }

    virtual void setPosition(SDL_Point position) { rectangle.setPosition(position); }

    Rectangle getBoundingRect() { return rectangle + label.getSDLRect(); }

protected:
    virtual void setLayout()
    {
    }
};
#endif // CONTROL_HPP
