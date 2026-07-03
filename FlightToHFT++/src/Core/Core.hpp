//
// Created by bird on 27/07/25.
//

#ifndef GAME_HPP
#define GAME_HPP


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <optional>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Exception.hpp>
#include "KeyboardEvents.hpp"
#include "PlayerSprite.hpp"
#include "BoundaryChecker.hpp"
#include "Background.hpp"

#include "Coin2.hpp"
#include "GameLevel.hpp"
#include "Menu.hpp"


class Game {
  private:
    Menu menu;
    bool Menubool = false;
 	sf::RenderWindow window;
    BackgroundManager manager;
    sf::Texture coinTexture;

  public:
    Game();
    void run();
    void update();
    void render();
    void exit();

};


#endif //GAME_HPP
