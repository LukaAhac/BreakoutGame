#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Constants.h"
#include "FadeScene.h"
#include "SceneManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BREAKOUT BY LUKA!");
    window.setFramerateLimit(FRAME_LIMIT);

    sf::Clock clock;
    std::unique_ptr<SceneManager> sm(SceneManager::getInstance());
    sm->changeScene(new FadeScene(&window, &clock, sm.get()));

    while (window.isOpen())
    {
        sm->nextFrame();
    }

    return 0;
}