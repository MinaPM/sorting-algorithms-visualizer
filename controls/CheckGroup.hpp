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

    void setLayout()
    {
        rectangle.setSize({0, 0});
        label.setPosition(rectangle.getPosition());
        rectangle = rectangle + label.getSDLRect();

        for (auto &checkBox : checkBoxes)
        {
            checkBox.setPosition({rectangle.getPosition().x, rectangle.getPosition().y + rectangle.getSize().y + checkBox.getSize().y + 5});
            rectangle = rectangle + checkBox.getBoundingRect();
        }
    }

    void resetCheckBoxes()
    {
        for (auto &checkBox : checkBoxes)
            checkBox.uncheck();
    }

public:
    CheckGroup(const std::string &text = "") : Control(text)
    {
        controlable = 0;
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(Colors::MAIN);
        rectangle.setFillColor(Colors::TRANSPARENT);
    }

    void setPosition(SDL_Point position)
    {
        rectangle.setPosition(position);
        setLayout();
    }

    void addCheckBox(const std::string &option)
    {
        checkBoxes.push_back(CheckBox(option));
        setLayout();
    }

    void setChoice()
    {
        resetCheckBoxes();
        checkBoxes[controlable].check();
        update();
    }

    bool clickWithin()
    {
        if (enabled && within())
            for (auto &checkBox : checkBoxes)
                if (checkBox.clickWithin())
                {
                    resetCheckBoxes();
                    controlable = &checkBox - &checkBoxes.front();
                    checkBox.check();
                    update();
                    return true;
                }

        return false;
    }

    void draw(SDL_Renderer *renderer)
    {
        Control::draw(renderer);

        for (auto &checkBox : checkBoxes)
            checkBox.draw(renderer);

        if (!enabled)
        {
            disabledRectangle.draw(renderer);
        }
    }

    Rectangle getBoundingRect() { return Control::getBoundingRect() + rectangle; }
};

#endif // SORTING_ALGORITHMS_CHECKGROUP_H
