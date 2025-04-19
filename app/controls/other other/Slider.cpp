#include "./header/Slider.hpp"

Slider::Slider(const std::string &text, int size, int current, int min, int max) : Control(text, size)
{
    width = 100;
    this->min = min;
    this->max = max;
    this->controlable = current;
    current_text = sf::Text(lable);
    current_text.setString(std::to_string(current));

    rectangle.setSize(sf::Vector2f(width, 20));
    current_rect.setSize(sf::Vector2f((float)((current - min) / (float)(max - min)) * width, 20));

    setColor(sf::Color::White, sf::Color::Red, sf::Color::White);
    setPosition(0, 0);
}

void Slider::setPosition(float x, float y)
{
    lable.setPosition(x, y);
    rectangle.setPosition(x, y + lable.getCharacterSize() + 10);
    current_rect.setPosition(rectangle.getPosition());
    current_text.setPosition(rectangle.getPosition().x + width + 5, rectangle.getPosition().y);
}

void Slider::setFont(const sf::Font &font)
{
    Control::setFont(font);
    current_text.setFont(font);
}

void Slider::setValue(sf::Vector2i point)
{
    if (!enabled || !clicked)
        return;

    float lenght = std::max(0.f, std::min((float)width, point.x - current_rect.getGlobalBounds().left));
    current_rect.setSize(sf::Vector2f(lenght, current_rect.getSize().y));
    controlable = (lenght / width) * (max - min) + min;
    current_text.setString(std::to_string(controlable));
}

int Slider::getPercentage() { return 100 * (max - controlable); }

void Slider::enable()
{
    Control::enable();
    setColor(rectangle.getFillColor(), rectangle.getOutlineColor(), lable.getFillColor());
}
void Slider::disable()
{
    Control::disable();
    setColor(rectangle.getFillColor(), rectangle.getOutlineColor(), lable.getFillColor());
}

void Slider::setColor(sf::Color fill, sf::Color outline, sf::Color text)
{
    Control::setColor(fill, outline, text);
    current_rect.setFillColor(outline);
    current_text.setFillColor(text);
}

void Slider::onValueChange(void (*func)(int))
{
    (*func)(controlable);
}

void Slider::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    Control::draw(rt, states);
    states.transform *= getTransform();
    rt.draw(current_rect, states);
    rt.draw(current_text, states);
}
