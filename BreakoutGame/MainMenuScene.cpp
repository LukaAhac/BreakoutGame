#include "MainMenuScene.h"

#include "Constants.h"
#include "GameScene.h"

void MainMenuScene::loadScene()
{
    playButtonTexture.loadFromFile(PLAY_BUTTON_TEXTURE_PATH);
    playButton = sf::RectangleShape(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    playButton.setTexture(&playButtonTexture);
    playButton.setPosition(BUTTON_X, PLAY_BUTTON_Y);

    quitButtonTexture.loadFromFile(QUIT_BUTTON_TEXTURE_PATH);
    quitButton = sf::RectangleShape(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    quitButton.setTexture(&quitButtonTexture);
    quitButton.setPosition(BUTTON_X, QUIT_BUTTON_Y);
}

void MainMenuScene::processEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (playButton.getGlobalBounds().contains((float)event.mouseButton.x / window->getSize().x * WINDOW_WIDTH,
                                                          (float)event.mouseButton.y / window->getSize().y * WINDOW_HEIGHT))
                {
                    sm->changeScene(new GameScene(window, clock, sm));
                    return;
                }
                else if (quitButton.getGlobalBounds().contains((float)event.mouseButton.x / window->getSize().x * WINDOW_WIDTH,
                                                               (float)event.mouseButton.y / window->getSize().y * WINDOW_HEIGHT))
                {
                    window->close();
                }
            }
        }
    }
}

void MainMenuScene::update()
{
}

void MainMenuScene::draw()
{
    window->draw(playButton);
    window->draw(quitButton);
}