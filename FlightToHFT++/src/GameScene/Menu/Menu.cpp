//
// Created by bird on 26/07/25.
//

#include "Menu.hpp"


Menu::Menu()
: item(0), font("/home/bird/CLionProjects/FlightToHFT++/assets/fonts/arial.ttf") , menuOptions{font, font, font}
{
std::string labels[MENU_OPTIONS] = {"Play", "Options", "Quit"};
for(int i = 0; i< MENU_OPTIONS; i++)
  {
    menuOptions[i].setFillColor(i == 0 ? SELECTED_COLOR : DEFAULT_COLOR);
    menuOptions[i].setString(labels[i]);
    menuOptions[i].setPosition({WIDTH / 2.f - 50, HEIGHT / 2.f + i * 60});
    }
}

void Menu::draw(sf::RenderWindow& window)
{

  for(int i = 0; i< MENU_OPTIONS; i++)
    window.draw(menuOptions[i]);
}
void Menu::notSelected()
{
    menuOptions[item].setFillColor(DEFAULT_COLOR);
}

void Menu::Selected()
{
    menuOptions[item].setFillColor(SELECTED_COLOR);
}

void Menu::moveUp()
{
    if (item == 0)
      return;
    notSelected();
    item--;
    Selected();
}

void Menu::moveDown()
{
    if (item < MENU_OPTIONS - 1)

{    notSelected();
    item++;
    Selected();
}
}

int Menu::getItemEnter()
{
    return item;
}