//
// Created by bird on 09/07/25.
//

#ifndef KEYBOARDEVENTS_HPP
#define KEYBOARDEVENTS_HPP

#include <SFML/Window/Event.hpp>
#include <iostream>
#include "Direction.hpp"

class KeyboardEvents {

  private:

  public:
    KeyboardEvents();
    Direction detectKey(const sf::Event& event);

};
#endif //KEYBOARDEVENTS_HPP
