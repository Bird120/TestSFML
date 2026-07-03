//
// Created by bird on 25/07/25.
//

#ifndef COIN_HPP
#define COIN_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Graphics/Rect.hpp>

class AnimatedCoin {
public:
    AnimatedCoin(const sf::Texture& texture, int frameCount, float frameTime)
        : texture(texture),sprite(texture), frameCount(frameCount), frameTime(frameTime), currentFrame(0), timeSinceLastFrame(0.f)
    {

        int frameWidth = texture.getSize().x / frameCount;
        int height = texture.getSize().y;

        // Préparer les rectangles de chaque frame
        for (int i = 0; i < frameCount; ++i) {
            frames.push_back(sf::IntRect({i * frameWidth, 0},{ frameWidth, height}));
        }

        sprite.setTextureRect(frames[0]);
    }

    void update(float deltaTime) {
        timeSinceLastFrame += deltaTime;
        if (timeSinceLastFrame >= frameTime) {
            timeSinceLastFrame = 0.f;
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(frames[currentFrame]);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void setPosition(float x, float y) {
        sprite.setPosition({x, y});
    }

private:
    const sf::Texture& texture;
    sf::Sprite sprite;
    std::vector<sf::IntRect> frames;
    int frameCount;
    float frameTime;
    int currentFrame;
    float timeSinceLastFrame;
};

#endif //COIN_HPP
