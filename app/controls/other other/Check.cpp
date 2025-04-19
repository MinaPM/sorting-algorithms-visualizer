#include "./header/Check.hpp"

CheckBox::CheckBox(const std::string &text, int size, bool status) : Control(text, size)
{
    controlable = status;
    rectangle.setSize(sf::Vector2f(15, 15));
    check_circle.setRadius(rectangle.getSize().x / 2);
    check_circle.setFillColor(sf::Color::Red);
    setPosition(0, 0);
}

void CheckBox::setPosition(float x, float y)
{
    rectangle.setPosition(x, y);
    check_circle.setPosition(rectangle.getPosition());
    lable.setPosition(rectangle.getPosition().x + rectangle.getGlobalBounds().width + 5,
                      rectangle.getPosition().y - lable.getGlobalBounds().height / 2);
}

void CheckBox::enable()
{
    enabled = true;
    setColor(sf::Color::Blue, sf::Color::White, sf::Color::Blue);
}
void CheckBox::disable()
{
    enabled = false;
    setColor(sf::Color(50, 50, 50), sf::Color::White, sf::Color(50, 50, 50));
}

void CheckBox::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    Control::draw(rt, states);
    states.transform *= getTransform();
    if (controlable)
        rt.draw(check_circle, states);
}

void CheckBox::setColor(sf::Color fill, sf::Color outline, sf::Color text)
{
    Control::setColor(fill, outline, text);
    check_circle.setFillColor(outline);
}

const bool &CheckBox::bindStatus() { return controlable; }

void CheckBox::toggle() { controlable = !controlable; }

void CheckBox::ckeck() { controlable = true; }

void CheckBox::unckeck() { controlable = false; }

bool CheckBox::clickWithin(sf::Vector2i point)
{
    if (enabled && within(point))
    {
        toggle();
        return true;
    }
    else
        return false;
}
