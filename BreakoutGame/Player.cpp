#include "Player.h"

void Player::updateScore(int scoreAdd)
{
    score += scoreAdd;
}

void Player::decreaseLives()
{
    lives--;
}