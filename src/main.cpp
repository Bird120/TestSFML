#include <SFML/Graphics.hpp>

int main()
{
    // Crée une fenêtre de 800x600 pixels
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Mon Projet SFML");

    // Crée un cercle vert de rayon 50
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    // Positionne le cercle au centre (approximatif)
    shape.setPosition({375.f, 275.f});

    // Boucle principale du jeu
    while (window.isOpen())
    {
        // Gestion des événements (fermeture de la fenêtre)
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Efface l'écran
        window.clear();

        // Dessine le cercle
        window.draw(shape);

        // Affiche le résultat à l'écran
        window.display();
    }

    return 0;
}