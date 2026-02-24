//
// Created by mina on 2/24/26.
//

#ifndef SORTING_ALGORITHMS_CHECKGROUP_H
#define SORTING_ALGORITHMS_CHECKGROUP_H
#include "Check.hpp"


class CheckGroup: public Control<int> {

    CheckGroup(){controlable=0;}

    std::vector<CheckBox> checkBoxes;

    void addCheckBoxe(std::string option) {
        checkBoxes.push_back(CheckBox(option));
    }
    void resetCheckBoxes() {
       for (auto &checkBox : checkBoxes) {
           checkBox.unckeck();
       }
    }

};


#endif //SORTING_ALGORITHMS_CHECKGROUP_H