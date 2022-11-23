#include "FadeScene.h"

#include "Constants.h"
#include "MainMenuScene.h"

void FadeScene::loadScene()
{
    image = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    tx.loadFromFile(WELCOME_IMAGE_PATH);
    image.setTexture(&tx);
    fadeInTime       = FADE_IN_TIME;
    displayImageTime = DISPLAY_TIME;
    fadeOutTime      = FADE_OUT_TIME;

    timer = fadeInTime;
    step  = FadeSceneStep::FadeIn;
}

void FadeScene::update()
{
    timer -= clock->restart().asSeconds();

    if (timer <= 0)
    {
        if (step == FadeSceneStep::FadeIn)
        {
            timer = displayImageTime;
            step  = FadeSceneStep::Display;
        }
        else if (step == FadeSceneStep::Display)
        {
            timer = fadeOutTime;
            step  = FadeSceneStep::FadeOut;
        }
        else
        {
            sm->changeScene(new MainMenuScene(window, clock, sm));
            return;
        }
    }

    if (step == FadeSceneStep::FadeIn)
    {
        image.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)((fadeInTime - timer) / fadeInTime * 255)));
    }
    else if (step == FadeSceneStep::Display)
    {
        //Nothing
    }
    else if (step == FadeSceneStep::FadeOut)
    {
        image.setFillColor(sf::Color(255, 255, 255, (sf::Uint8)(timer / fadeOutTime * 255)));
    }
}

void FadeScene::draw()
{
    window->draw(image);
}