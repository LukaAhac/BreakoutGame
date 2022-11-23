#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "SceneManager.h"

//Base scene class
//Scene defines how to process the events, updates scene elements and draws them on the screen
class BasicScene
{
protected:
    sf::RenderWindow* window;
    sf::Clock*        clock;
    SceneManager*     sm;

public:
    BasicScene(sf::RenderWindow* window, sf::Clock* clock, SceneManager* sm)
        : window(window)
        , clock(clock)
        , sm(sm){};
    virtual ~BasicScene(){};
    virtual void loadScene() = 0;
    virtual void processEvents();
    virtual void update() = 0;
    virtual void draw()   = 0;
    virtual void render() final;
};