#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Constants.h"

class Player : public sf::RectangleShape
{
private:
    int lives = 0;
    int score = 0;

public:
    Player(){}
    Player(sf::Vector2f position)
        : lives(INNITIAL_LIVES)
        , score(INNITIAL_SCORE)
        , RectangleShape(position)
    {
    }

    int getLives()
    {
        return lives;
    }
    int getScore()
    {
        return score;
    }

    void updateScore(int scoreAdd);
    void decreaseLives();
};