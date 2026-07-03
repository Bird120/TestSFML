//
// Created by bird on 26/07/25.
//

#ifndef MENU_HPP
#define MENU_HPP


#include <SFML/Graphics.hpp>
#include <array>

#include <SFML/Graphics/Text.hpp>

const sf::Color SELECTED_COLOR = sf::Color::Blue;
const sf::Color DEFAULT_COLOR = sf::Color::White;
#define MENU_OPTIONS 3
#define WIDTH 500
#define HEIGHT 400

class Menu {
  private:
      int item;
      sf::Font font;
      sf::Text menuOptions[MENU_OPTIONS];
  public:
    Menu();
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getItemEnter();
    void notSelected();
    void Selected();


};
#endif //MENU_HPP
