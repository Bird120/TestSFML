//
// Created by bird on 16/09/25.
//

#ifndef UPMOVING_HPP
#define UPMOVING_HPP

#include "Board.hpp"
#include "TypeMoving.hpp"
#include "HeightUp.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <iostream>

struct Upmoving2
{
  Upmoving2(float groundX_, float groundY_): groundX(groundX_), groundY(groundY_){}
  //Board board();
  bool upmoving= false;
    //default || down
  	  float groundX;
      float groundY; // sol (y position)

    //up
    float seuil_ = 270.f;
    float sizePlayer = 140.f;


    // for default moving
    Board* currentboard_;
    TypeMoving currenttypeMoving_;

    // vitesse ALL
    float velocityY = 0.f;       // vitesse verticale
 //up
    bool isJumping = false;
    float jumpStrength = -1400.f;  // vitesse initiale vers le haut

    float gravity = 1500.f;       // accélération vers le bas
	void handleMovements(float dt, sf::Sprite& sprite);
	void upKeybord(sf::Sprite& sprite, Board& board);
	void downKeybord(sf::Sprite& sprite);


    void setGravity(float value) { gravity = value;}
    float getGravity() { return gravity;}

    float getGroundY(){return groundY;}
    float getGroundX(){return groundX;}
    // HeightUp::First;
    void keyPressed(const float& value){
        if (!upmoving){

            //timeSinceLastFrame = 0;
            upmoving = true;
            velocityY = value;

            //up.velocityY = up.jumpStrength;

            std::cout <<" Key up has be pressed."<< "\n";
        }
    }


    void doTheMove(const float& dt, sf::Sprite& sprite, float seuil)
    {
            //std::cout << "vELOCITYy: " << velocityY <<"  dt:" << dt << "  pos y: " << sprite.getPosition().y << "  seuil: " << seuil <<  std::endl;
            sprite.move({0, velocityY * dt}); // offset = vitesse * temps écoulé

            // up
            if (currenttypeMoving_ == TypeMoving::UP){
            if (sprite.getPosition().y <= seuil - sizePlayer){
              			std::cout << " UP seuil: " << seuil <<  "  JE SUIS DANS UP : SEUIL -SIZEUP = "<< seuil - sizePlayer << " PLAYER: Y = "<< sprite.getPosition().y<< std::endl;
              sprite.setPosition({sprite.getPosition().x, seuil - sizePlayer});
                upmoving = false;

            }
            }
            else if (currenttypeMoving_ == TypeMoving::DEFAULT){

            if (seuil == 0){
              std::cout <<" Default: " << groundY << "   posx player: " << sprite.getPosition().x << std::endl;
              if (sprite.getPosition().y >= groundY){
                sprite.setPosition({sprite.getPosition().x, groundY});
                upmoving = false;
              }
            }
           }
           else if (currenttypeMoving_ == TypeMoving::DOWN){

            if (sprite.getPosition().y >= groundY){
                            std::cout <<" DOWN: " << groundY << "   posx player: " << sprite.getPosition().x << std::endl;

                sprite.setPosition({sprite.getPosition().x, groundY});
                upmoving = false;
            }
            }

    }

    void objectInMoving(const float& dt, sf::Sprite& sprite, const bool& border, TypeMoving upMoving)
     {
              if (upmoving){
                  velocityY += gravity * dt;
                  if (upMoving == TypeMoving::UP){
                    doTheMove(dt, sprite, currentboard_->upmovingValue);
                  }
                  else if (upMoving == TypeMoving::DEFAULT){

                    doTheMove(dt, sprite, 0);
                  }
                  else if (upMoving == TypeMoving::DOWN){
                    doTheMove(dt, sprite, getGroundY());
                  }
              }

     }


};



#endif //UPMOVING_HPP
