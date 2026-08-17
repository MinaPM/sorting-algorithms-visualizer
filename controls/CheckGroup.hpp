//
// Created by mina on 2/24/26.
//

#ifndef SORTING_ALGORITHMS_CHECKGROUP_H
#define SORTING_ALGORITHMS_CHECKGROUP_H
#include "Check.hpp"


class CheckGroup : public Control<int> {
protected:
    std::vector<CheckBox> checkBoxes;


    void setLayout() {
        SDL_Point padding{20, 10},
                position = rectangle.getPosition(),
                size = label.getSize();
        position.x += padding.x / 2.f;

        label.setPosition(position);
        position.y += size.y+ padding.y;

        for (auto &checkBox: checkBoxes) {
            position.y += padding.y;
            checkBox.setPosition(position);
            position.y += checkBox.getSize().y;
        }

        if (!checkBoxes.empty()) {
            size.y = (position.y - label.getPosition().y);
            size.y = std::abs(size.y);
        }
        size.x += padding.x;
        // size.y += padding.y;
        rectangle.setSize(size);
    }

    void resetCheckBoxes() {
        for (auto &checkBox: checkBoxes)
            checkBox.uncheck();
    }

public:
    CheckGroup(const std::string &text = "") : Control(text) {
        controlable = 0;
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(Colors::MAIN);
        rectangle.setFillColor(Colors::TRANSPARENT);
    }


    void setPosition(SDL_Point position) {
        rectangle.setPosition(position);
        setLayout();
    }

    void addCheckBox(const std::string &option) {
        checkBoxes.push_back(CheckBox(option));
        setLayout();
    }

    void setChoice() {
        resetCheckBoxes();
        checkBoxes[controlable].check();
        update();
    }


    bool clickWithin() {
        if (enabled && within())
            for (auto &checkBox: checkBoxes)
                if (checkBox.clickWithin()) {
                    resetCheckBoxes();
                    controlable = &checkBox - &checkBoxes.front();
                    checkBox.check();
                    update();
                    return true;
                }

        return false;
    }

    // SDL_Point getSize() {
    //     return rectangle.getSize();
    // }

    void draw(SDL_Renderer *renderer) {
        Control::draw(renderer);
  
        for (auto &checkBox: checkBoxes)
            checkBox.draw(renderer);
    }
    // void draw(sf::RenderTarget &rt, sf::RenderStates states) const override {
    //     Control::draw(rt, states);
    //     states.transform *= getTransform();
    //     for (auto &checkBox: checkBoxes)
    //         checkBox.draw(rt, states);
    // }
};


#endif //SORTING_ALGORITHMS_CHECKGROUP_H
