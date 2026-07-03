//
// Created by bird on 29/07/25.
//

#include "Level1.hpp"


Level1::Level1(sf::RenderWindow& w)
    :GameScene(w), begin(true)
{
    if (!music.openFromFile("assets/sounds/spaceadventure.ogg")) {
        std::cerr << "Level1: failed to load music" << std::endl;
    }
    music.play();
    createCoin(700.f, 400.f, 1);
    createCoin(600.f, 450.f, 1);

}

void Level1::initialize(bool state)
{
    //no need for the Level1
    (void)state;
    stateMenu(true);
    getPlayer().setterPosition(getWindow(),begin);
    this->begin = false;
}

Direction Level1::inputs(const sf::Event& event)
{
    return keyboard.detectKey(event);
}


bool Level1::update(const Direction& dir)
{
    if (getBoundaryChecker().canMove(dir, getPlayer(),20.0f,getWindow(), backgrounds))
    {
        getMovementSystem().changePosition(dir,20.0f, getPlayer());
        getPlayer().displayRightSprite(dir);
    }
    return false;
}




void Level1::display(sf::RenderWindow& window)
{
    auto deltaTime = getClock().restart().asSeconds();




    window.clear();
    updateAllCoins(deltaTime, backgrounds.getPage());

    //getWindow().draw(backgrounds.displayCurrentBackground());
    //accessAllCoins(CoinState::UPDATE, deltaTime, backgrounds.getPage(), window);
    //std::cout<< "AFFICHE BACKGROUND Level1" << std::endl;

    window.draw(backgrounds.displayCurrentBackground());
    window.draw(player.getSprite());

    //draw the sprite
    drawAllCoins(backgrounds.getPage(), window);
    //accessAllCoins(CoinState::DRAW, DefaultTimer, backgrounds.getPage(), window);

    getWindow().display();
}

void Level1::exit()
{

}