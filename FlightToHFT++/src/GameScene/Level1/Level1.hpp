//
// Created by bird on 29/07/25.
//

#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include "PopUp.hpp"
#include "GameScene.hpp"
#include "MovingDirection.hpp"

class Level1 : public GameScene
{
  private:
    bool begin;
  //PopUp pop;

  public:
    Level1(sf::RenderWindow& w);
    MovingDirection* movingDirection = nullptr;

    void initialize(bool state) override;
    Direction inputs(const sf::Event& event) override;
    bool update(const Direction& dir) override;
    void exit() override;
    void display(sf::RenderWindow& window) override;

};

#endif //LEVEL1_HPP
