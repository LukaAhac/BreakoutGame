#pragma once
#include "BasicScene.h"

enum class FadeSceneStep
{
    FadeIn,
    Display,
    FadeOut
};

//Class that is used to create welcome scene with fadeing effects over image
//After the effects end it transitions to main menu scene
class FadeScene : public BasicScene
{
private:
    sf::Texture        tx;
    sf::RectangleShape image;

    float fadeInTime;
    float displayImageTime;
    float fadeOutTime;

    float         timer;
    FadeSceneStep step;

public:
    using BasicScene::BasicScene;
    void loadScene() override;
    void update() override;
    void draw() override;
};