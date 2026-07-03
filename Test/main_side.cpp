
//#include <BackgroundManager.hpp>

#include "test.hpp"
#include <iostream>

#include "BackgroundManager.hpp"
#include "Coin2.hpp"
#include <SFML/Graphics/Sprite.hpp>

#include "Core/Core.hpp"

int main()
{


    auto core = std::make_unique<Core>();

    // Create the main window
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

    PlayerSprite player("/home/bird/CLionProjects/FlightToHFT++/assets/images/perso.png", window);

    // Create a graphical text to display
    const sf::Font font("./assets/fonts/arial.ttf");
    sf::Text text(font, "Fligh to HFT++", 10);
    sf::Music music;
    // Load a music to play
    //sf::Music music("./assets/sounds/spaceadventure.mp3");

    if (!music.openFromFile("assets/sounds/spaceadventure.ogg")) {
        std::cerr << "Failed to load music!" << std::endl;
        return 1;
    }
    //music.setLooping(true);
    // Play the music
    music.play();


    sf::Clock clock;

    while (window.isOpen())
    {

        player.setterPosition();

        KeyboardEvents keyboard_events;
        BoundaryChecker boundary_checker;
        MovementSystem movement_system;
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>()/* ||
                (event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape)*/)
                window.close();
            auto dir = keyboard_events.detectKey(*event);
            if (Menubool)
            {
                if (boundary_checker.canMove(dir,player,20.0f,window,manager ))
                {
                    std::cout<< "TRUE!!" << std::endl;
                    movement_system.changePosition(dir,20.0f, player);
                    player.displayRightSprite(dir);
                }
            }
            else if (!Menubool)
            {
                switch (dir)
                {
                case Direction::UP :
                    {
                            menu.moveUp();
                    break;
                    }

                case Direction::DOWN :
                    {
                        menu.moveDown();
                        break;
                    }
                case Direction::ENTER :
                    {
                        auto value  = menu.getItemEnter();
                        if (value == 0) Menubool = true;
                        else if (value == 2) window.close();
                        break;
                    }
                }

            }
        }

        float deltaTime = clock.restart().asSeconds();
        coin.update(deltaTime);

        window.clear();

        if (Menubool)
        {
                    // Draw the sprite
        window.draw(manager.displayCurrentBackground());

        window.draw(player.getSprite());

        coin.draw(window);  // ✅ affiche la pièce animée
        // Draw the string
        window.draw(text);
        }
        if (!Menubool)
            menu.draw(window);
        // Update the window
        window.display();
    }
}// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.