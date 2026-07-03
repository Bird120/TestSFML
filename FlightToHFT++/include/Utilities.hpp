//
// Created by bird on 18/07/25.
//

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include "PlayerSprite.hpp"

inline sf::Texture setTexture(const std::filesystem::path &filename){
    sf::Texture texture_tmp;
    if (texture_tmp.loadFromFile(filename))
        std::cerr << "Error: Loading texture from player, path:  " << filename << std::endl;
    return texture_tmp;
}
#endif //UTILITIES_HPP
