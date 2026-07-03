//
// Created by bird on 26/08/25.
//


#include <boost/asio/steady_timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/detail/chrono.hpp>
#include <boost/asio/co_spawn.hpp>


#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/detached.hpp>

#include <iostream>

#include <thread>
using boost::asio::co_spawn;

using boost::asio::use_awaitable;

using boost::asio::awaitable;
using boost::asio::steady_timer;
using boost::asio::io_context;
namespace chrono = boost::asio::chrono;

void handler(boost::system::error_code ec)
{
  if (ec){
        std::cout << "waiting" << std::endl;

    std::cout << ec.message() << std::endl;
  }
  else
    std::cout << "End" << std::endl;


}


  awaitable<void> action() {
  steady_timer timer(co_await boost::asio::this_coro::executor, chrono::seconds(5));
    std::cout << "waiting" << std::endl;

  co_await timer.async_wait(use_awaitable);
  }


#include "/home/bird/CLionProjects/FlightToHFT++/include/Utilities.hpp"
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Image.hpp>


constexpr int SECTIONS = 4;



sf::Font setFont(const std::filesystem::path &filename)
{
  sf::Font font;
      if (!font.openFromFile(filename)) // remplacer par une fonte existante
	  	std::cerr << "Error: FONT from player, path:  " << filename << std::endl;

return font;
}



struct Popup {
private:
      bool active = false;


  public:
  Popup(const std::string& question, const std::string& choice1, const std::string& choice2, const std::string& choice3)
      : labels{question, choice1, choice2, choice3}, texts({font_, question},{font_, choice1}, {font_, choice2}, {font_, choice3})
  		,texture(setTexture("/home/bird/CLionProjects/FlightToHFT++/assets/popup_pack_sfml/octopus_transparent.png")), sprite(texture),
          font_(setFont("/home/bird/CLionProjects/FlightToHFT++/assets/fonts/arial.ttf"))
  {
     sprite.setTexture(texture);
     sprite.setPosition({400, 200});
     sprite.setScale({0.8f, 0.75f});
  }
    std::string labels[SECTIONS];
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font_;
    sf::Text texts[SECTIONS] = {font_,font_,font_,font_};
    std::chrono::steady_clock::time_point startTime;
    const sf::Sprite& getSprite()  const { return sprite; }
    void display(sf::RenderWindow& window) const;
	const bool& getActive() const;
    void setStateActive(const bool& state);


};


void Popup::setStateActive(const bool& state)
{
  active = state;
}



const bool& Popup::getActive() const { return active; }


void Popup::display(sf::RenderWindow& window) const
{
   window.draw(getSprite());
    for(const auto& i : texts)
        window.draw(i);
}



class PopupManager
{
  private:

  public:
    PopupManager() = default;
    virtual ~PopupManager() = default;

    virtual Popup createPop(const std::string& question, const std::string& choice1, const std::string& choice2, const std::string& choice3);
    virtual void addPop(const Popup& popup);
    virtual void removeLastPop();
    virtual const Popup& extractLastPop();
    virtual std::vector<Popup>& getallpopup();
    std::vector<Popup> popups;

};


std::vector<Popup>& PopupManager::getallpopup()
{
  return popups;
}

Popup PopupManager::createPop(const std::string& question, const std::string& choice1, const std::string& choice2, const std::string& choice3)
{
       Popup p(question, choice1, choice2, choice3);

		for (int i = 0; i < SECTIONS; ++i) {
        p.texts[i].setFont(p.font_);
        p.texts[i].setString(p.labels[i]);
        p.texts[i].setCharacterSize(26);
        p.texts[i].setFillColor(sf::Color::Black);
        p.texts[i].setPosition({520, 500 + i * 80.f});
        }
        return p;
}

void PopupManager::addPop(const Popup& popup)
{
  popups.push_back(std::move(popup));
}


void PopupManager::removeLastPop()
{
  popups.pop_back();
}


const Popup& PopupManager::extractLastPop()
{
  return popups.back();
}



class MultithreadPopupManager :  public PopupManager
{
  public:
 MultithreadPopupManager() : PopupManager() {}
 ~MultithreadPopupManager() = default;

};



int main() {
    sf::RenderWindow window(sf::VideoMode({1400, 1000}), "Jeu avec popups");
	sf::Texture texture;
	std::unique_ptr<MultithreadPopupManager> p = std::make_unique<MultithreadPopupManager>();
    const int popupDuration = 5; // secondes
    const int popupInterval = 10; // secondes
    const int totalpopups = 6;
    //auto  popups =  p->getallpopup();

    for (int i = 0; i < totalpopups; ++i) {

        auto popup = p->createPop("Question ?", "Choice 1", "Choice 2", "Choice 3");

        p->addPop(std::move(popup));

    }

    auto startTime = std::chrono::steady_clock::now();

    while (window.isOpen()) {

        while ( const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        // Temps écoulé depuis le début
        auto now = std::chrono::steady_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        auto  popups =  p->getallpopup();

        // Activer les popups toutes les 10 secondes
        for (int i = 0; i < totalpopups; ++i) {

            int popupStart = i * popupInterval; // start du ième popup

            if (elapsedSeconds >= popupStart && elapsedSeconds < popupStart + popupDuration) {
				popups[i].setStateActive(true);
                popups[i].startTime = startTime + std::chrono::seconds(popupStart);
            } else {
                popups[i].setStateActive(false);
            }
        }

        // Rendu
        window.clear(sf::Color::White);
        // Ici ton jeu continue à tourner ...

        // Dessiner les popups actives
        for (const auto& pr : popups) {
            if (pr.getActive()) {
                pr.display(window);
            }
        }

        window.display();
    }
}
