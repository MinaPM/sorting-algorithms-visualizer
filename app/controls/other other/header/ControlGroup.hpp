#include "../../global.hpp"
#include "./Slider.hpp"

class ControlGroup : public sf::Drawable,
                     public sf::Transformable
{

public:
    Slider sliders[4];
    ControlGroup();

    // void setFunctions(PuzzleFunctions pFunction, bool enable)
    // {
    // }

    void update(sf::Vector2i point);

    void mouseReleased();

    void mouseClicked(sf::Vector2i point);

    void somethingHappened(sf::Event &event,sf::Vector2i point );

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;
};
