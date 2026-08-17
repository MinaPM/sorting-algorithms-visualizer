#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../src/global.hpp"
#include "../graphics/Rectangle.hpp"
template<typename Controlable>
class Control {
public:
    Rectangle rectangle;
    Text label;
    Controlable controlable;
    std::function<void()> onTrigger;

    bool enabled, clicked;

    Control()  {
        enabled = true;
        clicked = false;
        rectangle.setOutlineThickness(3);
        onTrigger = nullptr;
        // label.setCharacterSize(Resources::characterSize);
    }

    Control(const std::string &string) : Control() {
        label.setText(string);
    }

    // void setFont(const Font &font) { label.setFont(font); }
    void setString(const std::string &string) { label.setText(string); }

    void setColor(SDL_Color rectangleFill, SDL_Color rectangleOutline, SDL_Color text) {
        rectangle.setFillColor(rectangleFill);
        rectangle.setOutlineColor(rectangleOutline);
        label.setColor(text);
    }

    // bool within() { return rectangle.getGlobalBounds().contains((sf::Vector2f) Resources::mousePosition()); }
    bool within() {
        SDL_Point mousePos = Resources::mousePosition();
        SDL_Rect rect = rectangle.getSDLRect();
        return SDL_PointInRect(&mousePos, &rect); }
        
    bool clickWithin() { return clicked = within(); }
    void mouseReleased() { clicked = false; }

    bool isEnabled() { return enabled; }

    void enable() {
        enabled = true;
        // sf::Color c1(rectangle.getFillColor()), c2(rectangle.getOutlineColor()), c3(label.getFillColor());
        // c1.a = 255;
        // c2.a = 255;
        // c3.a = 255;
        // setColor(c1, c2, c3);
    }

    void disable() {
        enabled = false;
        // sf::Color c1(rectangle.getFillColor()), c2(rectangle.getOutlineColor()), c3(label.getFillColor());
        // c1.a = 124;
        // c2.a = c1.a;
        // c3.a = c1.a;
        // setColor(c1, c2, c3);
    }

    Controlable *bindControlable() { return &controlable; }

    void setOnTrigger(std::function<void()> func) { onTrigger = func; }

    void update() {
        if (onTrigger)
            onTrigger();
    }

    void alignLeft() { label.setPosition({rectangle.getPosition().x, label.getY()}); }

    SDL_Point getPosition() {
        return rectangle.getPosition();
    }

    SDL_Point getSize() {
        return rectangle.getSize();
    }

    void draw(SDL_Renderer *renderer) {
        rectangle.draw(renderer);
        label.draw(renderer);
    }

    // void draw(sf::RenderTarget &rt, sf::RenderStates states) const override {
    //     states.transform *= getTransform();
    //     rt.draw(rectangle, states);
    //     rt.draw(label, states);
    // }


    virtual void setPosition(SDL_Point position) { rectangle.setPosition(position); }

protected:
    virtual void setLayout() {
    }
};
#endif // CONTROL_HPP
