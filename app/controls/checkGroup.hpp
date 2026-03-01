//
// Created by mina on 2/24/26.
//

#ifndef SORTING_ALGORITHMS_CHECKGROUP_H
#define SORTING_ALGORITHMS_CHECKGROUP_H
#include "Check.hpp"


class CheckGroup : public Control<int> {
protected:
    std::vector<CheckBox> checkBoxes;


    void setLayout() override {
        sf::Vector2f padding(20, 10),
                position = rectangle.getPosition(),
                size = label.getGlobalBounds().size;
        position.x += padding.x / 2.f;

        label.setPosition(position);
        position.y += size.y;

        for (auto &checkBox: checkBoxes) {
            position.y += padding.y;
            checkBox.setPosition(position);
            position.y += checkBox.getSize().y;
        }

        if (!checkBoxes.empty()) {
            size.y = (position - label.getGlobalBounds().position).y;
            size.y = std::abs(size.y);
        }
        rectangle.setSize(size + padding);
    }

    void resetCheckBoxes() {
        for (auto &checkBox: checkBoxes)
            checkBox.uncheck();
    }

public:
    CheckGroup(const std::string &text = "") : Control(text) {
        controlable = 0;
        rectangle.setOutlineThickness(1);
        rectangle.setFillColor(sf::Color::Transparent);
    }


    void setPosition(sf::Vector2f position) override {
        rectangle.setPosition(position);
        setLayout();
    }

    void addCheckBox(const std::string &option) {
        checkBoxes.push_back(CheckBox(option));
        setLayout();
    }


    bool clickWithin() {
        if (enabled && within())
            for (auto &checkBox: checkBoxes)
                if (checkBox.clickWithin()) {
                    resetCheckBoxes();
                    controlable = &checkBox - &checkBoxes.front();
                    checkBox.check();
                    return true;
                }

        return false;
    }

    sf::Vector2f getSize() {
        return rectangle.getSize();
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override {
        Control::draw(rt, states);
        states.transform *= getTransform();
        for (auto &checkBox: checkBoxes)
            checkBox.draw(rt, states);
    }
};


#endif //SORTING_ALGORITHMS_CHECKGROUP_H
