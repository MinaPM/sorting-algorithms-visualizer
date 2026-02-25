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
        sf::Vector2f position = label.getPosition(), padding(0, 50);
        auto height = checkBoxes.empty() ? 10 : (position - checkBoxes.back().getPosition()).y;
        rectangle.setSize({4, height});

        rectangle.setPosition(position);
        for (auto& checkBox : checkBoxes)
        {
            position += padding;
            checkBox.setPosition(position);
            position += checkBox.getSize();
        }
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
    CheckGroup() { controlable = 0; }

    CheckGroup(const std::string& text) : Control(text) { controlable = 0; }


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
