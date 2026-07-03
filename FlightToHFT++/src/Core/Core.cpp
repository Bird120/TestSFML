//
// Created by bird on 27/07/25.
//

#include "Game.hpp"

Game::Game()
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "SFML window");
    bool Menubool = false;
    Menu menu;
    BackgroundManager manager;

    sf::Texture coinTexture;
    //coinTexture.loadFromFile("/home/bird/CLionProjects/FlightToHFT++/assets/images/coin.png");
    if (!    coinTexture.loadFromFile("/home/bird/CLionProjects/FlightToHFT++/assets/images/coin.png")) {
        std::cerr << "Erreur : impossible de charger l'image du coin !" << std::endl;
    }

    AnimatedCoin coin(coinTexture, 8, 0.1f); // 8 frames, 0.1s par frame
    coin.setPosition(400.f, 300.f);
    coin.setScale(0.2f, 0.4f );  // 50% de la taille


}

void Game::run()
{

}