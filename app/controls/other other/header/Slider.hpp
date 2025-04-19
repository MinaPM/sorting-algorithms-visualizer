#include "Control.hpp"

class Slider : public Control<int>
{

public:
    sf::Text current_text;
    sf::RectangleShape current_rect;
    int min, max, width;

    Slider(const std::string &text, int size, int current, int min, int max);

    void setPosition(float x, float y);

    void setFont(const sf::Font &font);

    void setValue(sf::Vector2i point);

    int getPercentage();

    void enable();
    void disable();

    void setColor(sf::Color fill, sf::Color outline, sf::Color text);

    void onValueChange(void (*func)(int));

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;
};