//
// Created by mina on 2/24/26.
//

#ifndef SORTING_ALGORITHMS_CHECKGROUP_H
#define SORTING_ALGORITHMS_CHECKGROUP_H
#include "Check.hpp"


class CheckGroup : public Control<int>
{
public:
    CheckGroup() { controlable = 0; }

    CheckGroup(const std::string &text):Control(text) { controlable = 0; }

    std::vector<CheckBox> checkBoxes;

    void addCheckBox(std::string option)
    {
        checkBoxes.push_back(CheckBox(option));
    }

    void resetCheckBoxes()
    {
        for (auto& checkBox : checkBoxes)
        {
            checkBox.unckeck();
        }
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

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        Control::draw(rt, states);
        states.transform *= getTransform();
        for (auto& checkBox:checkBoxes)
            checkBox.draw(rt,states);

    }

};


#endif //SORTING_ALGORITHMS_CHECKGROUP_H
