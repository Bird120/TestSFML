//
// Created by bird on 16/09/25.
//

#include "Upmoving.hpp"



void Upmoving2::downKeybord(sf::Sprite& sprite)
{
    if (sprite.getPosition().y != getGroundY()){
        setGravity(2000.f);
        keyPressed(getGravity());
        currenttypeMoving_= TypeMoving::DOWN;
    }
}




void Upmoving2::upKeybord(sf::Sprite& sprite, Board& board)
{

    if (board.canGoLeftOnBoard(sprite.getPosition().x) || board.canGoRightOnBoard(sprite.getPosition().x))
    {
        currenttypeMoving_= TypeMoving::UP;

        std::cout << " Player pret de board Height -> "<< board.height_ << std::endl;
        keyPressed(HeightUp::Fourth);
    }
    else if (sprite.getPosition().y == getGroundY())
    {
        currenttypeMoving_=  TypeMoving::DEFAULT;
        //if (down_temp == TypeMoving::DEFAULT){ std::cout << "yes ca fonction recupere bien TypeMoving::DEFAULT" << std::endl; }
        std::cout << "le segfault " << std::endl;
        groundY = sprite.getPosition().y;
        currentboard_ = nullptr;
        std::cout << " Player pret de board Height -> "<< HeightUp::First << std::endl;

        keyPressed(HeightUp::First);
    }
}

void Upmoving2::handleMovements(float dt, sf::Sprite& sprite)
{
    //if (currenttypeMoving_ == TypeMoving::DEFAULT){ std::cout << "yes ca fonction recupere bien TypeMoving::DEFAULT" << std::endl; }

    if (!isJumping &&  currentboard_ != nullptr && currenttypeMoving_ ==  TypeMoving::UP)
    {
        objectInMoving(dt,sprite,true, TypeMoving::UP);
    }
    else if (!isJumping && currentboard_ != nullptr && currenttypeMoving_ == TypeMoving::DOWN )
        objectInMoving(dt,sprite,true, TypeMoving::DOWN);
    else if (!isJumping &&  currentboard_ == nullptr && currenttypeMoving_ ==  TypeMoving::DEFAULT)
    {
        objectInMoving(dt,sprite,true,  currenttypeMoving_);
    }
}
