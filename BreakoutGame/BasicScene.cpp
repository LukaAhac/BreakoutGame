#include "BasicScene.h"

void BasicScene::processEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void BasicScene::render()
{
    window->clear();
    draw();
    window->display();
}