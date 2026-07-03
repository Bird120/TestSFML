//
// Created by bird on 09/07/25.
//

#include "KeyboardEvents.hpp"

KeyboardEvents::KeyboardEvents()
{

}

Direction KeyboardEvents::detectKey(const sf::Event& event)
{
	  Direction dir = Direction::DEFAULT;
      if (const auto* keyPressed = event.getIf<sf::Event::KeyReleased>())
        if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
        {
            std::cout<< "key right has been pressed!" << std::endl;
            dir = Direction::RIGHT;

        }
      return dir;
}