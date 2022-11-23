#pragma once
#include "BasicScene.h"

//Class that is used to create main menu scene with two simple buttons
//One starts and the other one quits the game
class MainMenuScene : public BasicScene
{
private:
    sf::Texture        playButtonTexture;
    sf::RectangleShape playButton;
    sf::Texture        quitButtonTexture;
    sf::RectangleShape quitButton;

public:
    using BasicScene::BasicScene;
    void loadScene() override;
    void processEvents() override;
    void update() override;
    void draw() override;
};