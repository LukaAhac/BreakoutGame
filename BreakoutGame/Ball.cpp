#include "Ball.h"

#include "Constants.h"
#include "Player.h"

void Ball::setAngle(double angle)
{
    if (angle > ANGLE360)
    {
        this->angle = angle - ANGLE360;
    }
    else if (angle < ANGLE0)
    {
        this->angle = angle + ANGLE360;
    }
    else
    {
        this->angle = angle;
    }
}

bool Ball::goingUp()
{
    return angle > ANGLE180;
}

bool Ball::goingLeft()
{
    return angle > ANGLE90 && angle < ANGLE270;
}

void Ball::move(float dt)
{
    setPosition(getPosition().x + (float)cos(angle) * velocity * dt, getPosition().y + (float)sin(angle) * velocity * dt);
}

void Ball::updateAngle(CollisionType type, Player* player)
{
    switch (type)
    {
    case CollisionType::Top:
        if (goingLeft())
        {
            setAngle(ANGLE180 - (angle - ANGLE180));
        }
        else
        {
            setAngle(ANGLE360 - angle);
        }
        break;

    case CollisionType::Bottom:
        if (goingLeft())
        {
            setAngle(ANGLE270 - (angle - ANGLE90));
        }
        else
        {
            setAngle(ANGLE360 - angle);
        };
        break;

    case CollisionType::Right:
        if (goingUp())
        {
            setAngle(ANGLE180 + (ANGLE360 - angle));
        }
        else
        {
            setAngle(ANGLE180 - angle);
        }
        break;

    case CollisionType::Left:
        if (goingUp())
        {
            setAngle(ANGLE360 - (angle - ANGLE180));
        }
        else
        {
            setAngle(ANGLE180 - angle);
        }
        break;

    case CollisionType::Raft:
        float ballX   = getPosition().x + getSize().x / 2;
        float playerX = player->getPosition().x;

        if (ballX > playerX)
        {
            if (ballX < playerX + RAFT_BOUNCE_PARTS)
            {
                angle = BOUNCE_RIGHT_60;
            }
            else if (ballX < playerX + RAFT_BOUNCE_PARTS * 2)
            {
                angle = BOUNCE_RIGHT_45;
            }
            else
            {
                angle = BOUNCE_RIGHT_30;
            }
        }
        else
        {
            if (ballX > playerX - RAFT_BOUNCE_PARTS)
            {
                angle = BOUNCE_LEFT_60;
            }
            else if (ballX > playerX - RAFT_BOUNCE_PARTS * 2)
            {
                angle = BOUNCE_LEFT_45;
            }
            else
            {
                angle = BOUNCE_LEFT_30;
            }
        }
        break;
    }
}

void Ball::spawn()
{
    setPosition(BALL_SPAWN_X, BALL_SPAWN_Y);
    angle = BOUNCE_RIGHT_45;
}