//
// Created by mina on 2/24/26.
//

#ifndef SORTING_ALGORITHMS_CHECKGROUP_H
#define SORTING_ALGORITHMS_CHECKGROUP_H
#include "Check.hpp"


class CheckGroup : public Control<int>
{
protected:
    std::vector<CheckBox> checkBoxes;


    void setLayout() override
    {
        sf::Vector2f position = label.getPosition(), padding(10, 10), size = {0, 0};
        rectangle.setPosition(position);
        position.y += label.getGlobalBounds().size.y;
        float x = 0, y = 0;
        x = label.getGlobalBounds().size.x ;

        for (auto& checkBox : checkBoxes)
        {
            position.y += padding.y;
            checkBox.setPosition(position);
            position.y += checkBox.getSize().y;
            x = std::max(x, checkBox.getSize().x);
            y = checkBox.getPosition().y + checkBox.getSize().y;
        }
        rectangle.setSize({x+10,y- label.getGlobalBounds().position.y+10+10});
        rectangle.setPosition(label.getPosition()-sf::Vector2f(5,5));
    }

    void setPosition() { setPosition(label.getPosition()); }

    void resetCheckBoxes()
    {
        for (auto& checkBox : checkBoxes)
        {
            checkBox.uncheck();
        }
    }

public:
    CheckGroup(const std::string& text = "") : Control(text)
    {
        controlable = 0;
        rectangle.setOutlineThickness(1);
        rectangle.setFillColor(sf::Color::Transparent);
    }


    void setPosition(sf::Vector2f position) override
    {
        label.setPosition(position);
        setLayout();
    }

    void addCheckBox(std::string option)
    {
        checkBoxes.push_back(CheckBox(option));
        setPosition();
    }


    bool clickWithin()
    {
        if (enabled)
            for (auto& checkBox : checkBoxes)
                if (checkBox.clickWithin())
                {
                    controlable = &checkBox - &checkBoxes.front();
                    return true;
                }

        return false;
    }

    sf::Vector2f getSize()
    {
        return rectangle.getSize();
    }

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
    {
        Control::draw(rt, states);
        states.transform *= getTransform();
        for (auto& checkBox : checkBoxes)
            checkBox.draw(rt, states);
    }
};


#endif //SORTING_ALGORITHMS_CHECKGROUP_H
