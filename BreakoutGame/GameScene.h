#pragma once
#include "SFML/Audio.hpp"

#include "BasicScene.h"

#include "Ball.h"
#include "Brick.h"
#include <float.h>
#include "Level.h"
#include "Player.h"


//Gameplay scene, contains game labels, boarders, bricks, ball and player driven raft
//Also defines game "physics"
class GameScene : public BasicScene
{
private:
    std::vector<sf::RectangleShape> gameBoarder;
    Player                          player;
    Ball                            ball;
    Level                           level;
    std::vector<Brick>              bricks;
    int                             currentLevel = 1;

    double              collisionDistance;
    float               collisionX = 0;
    float               collisionY = 0;
    std::vector<Brick*> collidingBricks;

    int winConditionBricksLeft = 0;

    sf::Font font;
    sf::Text levelLabel;
    sf::Text levelAmount;
    sf::Text scoreLabel;
    sf::Text scoreAmount;
    sf::Text livesLabel;
    sf::Text livesAmount;

    sf::SoundBuffer wallHitSoundBuff;
    sf::Sound       wallHitSound;
    sf::SoundBuffer raftHitSoundBuff;
    sf::Sound       raftHitSound;

public:
    using BasicScene::BasicScene;
    void processEvents() override;
    void loadScene() override;
    void update() override;
    void draw() override;

    void createBoarder();
    void createBall();
    void createRaft();
    void createLevel();
    void createLabels();
    void loadSounds();

    double calcDistance(sf::Vector2f x, sf::Vector2f y);
    void   horizontalBrickCollisonCheck(float k, float b, float y, Brick* brick);
    void   bricksUpdate();
    void   checkBoarderCollisions();
    void   checkRaftCollision();
    void   checkBrickCollisions();
    void   calculateNextBrickCollision();
};