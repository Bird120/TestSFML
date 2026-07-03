
#include "test.hpp"
#include <iostream>
#include "PlayerSprite.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({1400, 1000}), "SFML window");

    // Load a sprite to display
    //const sf::Texture texture("./assets/images/perso.png", false, sf::IntRect({10, 10}, {32, 32}));
    //PlayerSprite player("./assets/images/perso.png");
    sf::Texture texture;
    texture.loadFromFile("./assets/images/perso.png");
    sf::Sprite sprite(texture);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));


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
    // Play the music
    music.play();
    float Xposition = 0.0f;
    // Start the game loop
    while (window.isOpen())
    {
        //sf::Event event;
        // Process events
        sprite.setPosition(sf::Vector2f(Xposition, 0.0f));

        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
            {
                std::cout<< "key right has been pressed!" << std::endl;
                Xposition += 8.0f;
            }

        }
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
}// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.