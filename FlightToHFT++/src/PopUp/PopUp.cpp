//
// Created by bird on 17/08/25.
//

#include "PopUp.hpp"


PopUp::PopUp()
    : texture(setTexture("/home/bird/CLionProjects/FlightToHFT++/assets/popup_pack_sfml/pieuvre.png")),
        sprite(texture)
{
    sprite.setTextureRect({{10, 10}, {50, 30}});
    sprite.setPosition({200.f, 25.f});
}

sf::Sprite& PopUp::getSprite()
{
  return sprite;
}