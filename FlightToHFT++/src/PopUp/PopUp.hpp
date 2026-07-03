//
// Created by bird on 17/08/25.
//

#ifndef POPUP_HPP
#define POPUP_HPP


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include "Utilities.hpp"


class PopUp
{
  protected:
    const sf::Texture texture;
    sf::Sprite sprite;
  public:
    PopUp();
    sf::Sprite& getSprite();



};
#endif //POPUP_HPP
