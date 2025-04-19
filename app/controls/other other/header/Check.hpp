#include "Control.hpp"

class CheckBox : public Control<bool>
{

public:
    sf::CircleShape check_circle;
    CheckBox(const std::string &text, int size, bool status = false);

    void setPosition(float x, float y);

    void enable();
    void disable();

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;

    void setColor(sf::Color fill, sf::Color outline, sf::Color text);

    const bool &bindStatus();

    void toggle();

    void ckeck();

    void unckeck();

    bool clickWithin(sf::Vector2i point);
};