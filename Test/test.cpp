//
// Created by bird on 17/08/25.
//






/*


#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <thread>
#include <random>

using namespace boost::asio;
using namespace std::chrono_literals;

struct Scene {
    io_context ctx;
    std::thread th;

    virtual ~Scene() { stop(); }

    virtual void start() {
        th = std::thread([this]() { ctx.run(); });
    }

    virtual void stop() {
        ctx.stop();
        if (th.joinable()) th.join();
    }

    // Par défaut, une scène n'a pas de popups
    virtual void initPopups() {}
};

struct LevelScene : public Scene {
    int popupCount;
    std::string name;

    LevelScene(int count, std::string n) : popupCount(count), name(std::move(n)) {}

    void initPopups() override {
        for (int i = 0; i < popupCount; ++i) {
            co_spawn(ctx, popup_task(ctx.get_executor(), name, i), detached);
        }
    }

    static awaitable<void> popup_task(any_io_executor exec, std::string sceneName, int id) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(3, 6); // temps test rapide

        while (true) {
            int seconds = dist(gen);
            steady_timer timer(exec, std::chrono::seconds(seconds));
            co_await timer.async_wait(use_awaitable);

            std::cout << "[SCENE: " << sceneName
                      << "] Popup " << id
                      << " déclenché après " << seconds << "s\n";
        }
        co_return;
    }
};

// Menu n’a pas besoin de popups → hérite sans override
struct MenuScene : public Scene {};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game with Scenes");

    Scene* currentScene = nullptr;
    int sceneIndex = 0;

    auto loadScene = [&](int index) {
        if (currentScene) {
            currentScene->stop();
            delete currentScene;
        }

        if (index == 0) { // Menu
            currentScene = new MenuScene();
        } else if (index == 1) { // Level1
            currentScene = new LevelScene(6, "Level1");
        } else if (index == 2) { // Level2
            currentScene = new LevelScene(6, "Level2");
        }

        currentScene->initPopups();
        currentScene->start();

        std::cout << "== Nouvelle scène chargée : " << index << " ==\n";
    };

    loadScene(sceneIndex);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Space) {
                    sceneIndex = (sceneIndex + 1) % 3;
                    loadScene(sceneIndex);
                }
            }
        }

        window.clear();
        window.display();
    }

    if (currentScene) {
        currentScene->stop();
        delete currentScene;
    }
}

________________________________________________
*/















#include <boost/asio.hpp>
#include <iostream>
#include <boost/asio/io_context.hpp>


#include <boost/asio/steady_timer.hpp>
//#include <boost/asio/experimental/awaitable_operators.hpp>


/*#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Exception.hpp>
#include "include/Utilities.hpp"
#define WIDTH 500
#define HEIGHT 400

const sf::Color SELECTED_COLOR = sf::Color::Blue;
const sf::Color DEFAULT_COLOR = sf::Color::White;
constexpr int SECTIONS = 4;
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>






#include <boost/asio/experimental/co_spawn.hpp>

#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>

namespace asio = boost::asio;

//using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::steady_timer;

using boost::asio::awaitable;
//using boost::asio::experimental::co_spawn;
using boost::asio::detached;

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include <random>

#include <vector>


awaitable<void> wait_seconds(asio::any_io_executor exec, int seconds) {
    steady_timer timer(exec);
    timer.expires_after(std::chrono::seconds(seconds));
    co_await timer.async_wait(boost::asio::use_awaitable);
}



void handler(const boost::system::error_code& error, bool& lili)
{
  if (error)
  {
    lili = true;

  }
}

/*
// attendre un nombre aléatoire
awaitable<void> wait_random_seconds(asio::any_io_executor exec, int min, int max, bool &lili) {
                        std::cout << "bug1\n";

    static std::mt19937 gen(std::random_device{}());
                          std::cout << "bug2\n";

    std::uniform_int_distribution<> dist(min, max);
    int duration = dist(gen);
                          std::cout << "bug3\n";

    steady_timer timer(exec);
                          std::cout << "bug4\n";

    timer.expires_after(std::chrono::seconds(duration));
                          std::cout << "bug5\n";

    co_await timer.async_wait([&lili](const boost::system::error_code& error) {
    if (error) {
        lili = true;
    }
});//timer.async_wait(handler);
}
*/

awaitable<void> wait_random_seconds(asio::any_io_executor exec, int min, int max, bool &lili) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(min, max);
    int duration = dist(gen);

    steady_timer timer(exec);
    timer.expires_after(std::chrono::seconds(duration));

    try {
        co_await timer.async_wait(asio::use_awaitable);
    } catch (const boost::system::system_error&) {
        lili = true;
    }
}






class PopUp
{
    const sf::Texture cadre;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text Options[SECTIONS];
    std::string labels[SECTIONS];

  public:
    PopUp(const std::string& question, const std::string& choice1, const std::string& choice2, const std::string& choice3);
    void display(sf::RenderWindow& window) const;
    bool shouldShowPopup;


};
 PopUp:: PopUp(const std::string& question, const std::string& choice1, const std::string& choice2, const std::string& choice3)
    : cadre(setTexture("/home/bird/CLionProjects/FlightToHFT++/assets/popup_pack_sfml/pieuvre.png")),
        sprite(cadre), font("/home/bird/CLionProjects/FlightToHFT++/assets/fonts/arial.ttf"),
        Options{font, font, font, font}, labels(question, choice1, choice2, choice3)
{
    sprite.setTextureRect({{10, 10}, {500, 800}});
    sprite.setPosition({200.f, 25.f});
        //std::string labels[SECTIONS] = {"What is your favorite color?", "Blue", "Red", "Pink"};

    for (int i = 0; i < SECTIONS; i++)
    {
        Options[i].setFillColor(i == 0 ? SELECTED_COLOR : DEFAULT_COLOR);
        Options[i].setString(labels[i]);
        Options[i].setPosition({WIDTH / 2.f - 50, (HEIGHT / 2.f + (i * 20))});
    }
}


void PopUp::display(sf::RenderWindow& window) const
{
    window.draw(sprite);
    for(const auto& i : Options)
        window.draw(i);
}




class PopupManager
{
  private:
    std::vector<PopUp> pops;
    std::thread thread;

    protected:
    asio::io_context ctx;


  public:
    PopupManager() = default;
    bool shouldShowPopup =  false;
    virtual void run();
    virtual void initial(sf::RenderWindow& window, PopUp& popup)
    {
      co_spawn(ctx, [exec = ctx.get_executor(), this, &window, &popup]() -> awaitable<void> {
    for (int i = 0; i < 2; ++i) {
              std::cout << "avant wait\n";

        co_await wait_random_seconds(exec, 2, 5, this->shouldShowPopup);
        /*std::cout << "bug\n";

        popup.display(window);
                      std::cout << "bug6\n";
        this->shouldShowPopup = true;

        std::cout << "[POPUP] Hello!\n";
        co_await wait_seconds(exec, 3);*/
        this->shouldShowPopup = false;

        std::cout << "[POPUP] Gone!\n";
    }
    co_return ;
}, detached);
    }
       /* co_spawn(ctx, [this]() -> awaitable<void> {
       co_await wait_random_seconds(ctx.get_executor(), 2, 5);
       this->shouldShowPopup = true;
       co_return;
   }, detached);
        }*/
    virtual void stopPopUp();
    virtual void addPopUp(const PopUp& popup);

    virtual void deletePopUp();
    virtual const PopUp& getLastElementPopUp();
    virtual std::size_t PopUpSize() const;


};

void PopupManager::stopPopUp()
{
  thread.join();
}



void PopupManager::addPopUp(const PopUp& popup)
{
  pops.push_back(popup);

}

std::size_t PopupManager::PopUpSize() const
{
    return pops.size();

}

void PopupManager::deletePopUp()
{
    pops.pop_back();

}

const PopUp& PopupManager::getLastElementPopUp()
{
    return pops.back();

}



void PopupManager::run()
{
    thread = std::thread ([this]() {ctx.run();});
}

class MultithreadingPopUpManager : public PopupManager
{
  private:
    asio::io_context io_context_;
  public:
    MultithreadingPopUpManager() : PopupManager() {}
};


/*      co_spawn(ctx, [exec = ctx.get_executor(), item]() -> awaitable<void> {
    for (int i = 0; i < 2; ++i) {
        co_await wait_random_seconds(exec, 2, 5);
        std::cout << "[POPUP] Hello!\n";
        co_await wait_seconds(exec, 3);
        std::cout << "[POPUP] Gone!\n";
        std::cout << "dans coroutine fin: "<< item << std::endl;
    }
    co_return ;
}, detached);
    }*/



int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "SFML window");
    PopUp pop1("Question ?", "Choix 1", "Choix 2", "Choix 3");

    pop1.shouldShowPopup = true; // for testing
	auto manager =  std::make_shared<MultithreadingPopUpManager>();
    manager->initial(window, pop1);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
{
            if (event->is<sf::Event::Closed>())    //(event->type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        manager->run();
		if (manager->shouldShowPopup) {
                  std::cout << "dedans " << std::endl;
                pop1.display(window);

		}


        window.display();
    }
}

/*
int main() {

  std::unique_ptr<MultithreadingPopUpManager> pop  = std::make_unique<MultithreadingPopUpManager>();
  PopUp pop1("question", "choix1","choix2", "choix3");
  PopUp pop2("question2", "choix1","choix2", "choix3");

  pop->addPopUp(pop1);
  pop->addPopUp(pop2);



    sf::RenderWindow window(sf::VideoMode({1200, 800}), "SFML window");



    while (window.isOpen())
    {


        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>()
                // (event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape))
                window.close();
            }

                        window.clear();


        if (pop->shouldShowPopup) {
            auto& last = pop->getLastElementPopUp();
            last.display(window);
            pop->deletePopUp();

        }

            window.display();



    }
}

*/



/*
#include <iostream>

int main() {
    std::mt19937 gen(42);  // seed fixe
    std::uniform_int_distribution<> dist(1, 100);

    std::cout << dist(gen) << std::endl;
}
*/