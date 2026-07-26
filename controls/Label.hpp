//
// Created by Mina on 2/25/26.
//

#ifndef SORTING_ALGORITHMS_LABEL_H
#define SORTING_ALGORITHMS_LABEL_H
#include "../global.hpp"

class Label:public sf::Drawable, public sf::Transformable
{
    sf::Text text;

    Label() : text(Resources::font)
    {
    }

    void setFont(const sf::Font& font) { text.setFont(font); }
    void setString(const std::string& string) { text.setString(string); }
    std::string getString() { text.getString(); }


};


#endif //SORTING_ALGORITHMS_LABEL_H
