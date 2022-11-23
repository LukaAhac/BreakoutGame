#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

enum class CollisionType
{
    Top,
    Bottom,
    Left,
    Right,
    Raft
};
class Player;

class Ball : public sf::RectangleShape
{
private:
    float  velocity = 0;
    double angle = 0;

public:
    Ball(){}
    Ball(sf::Vector2f size, float velocity, double angle)
        : velocity(velocity)
        , angle(angle)
        , sf::RectangleShape(size){};

    float getVelocity()
    {
        return velocity;
    }
    double getAngle()
    {
        return angle;
    }

    void setVelocity(float velocity)
    {
        this->velocity = velocity;
    }
    void setAngle(double angle);

    bool goingUp();
    bool goingLeft();

    void move(float dt);
    void spawn();
    void updateAngle(CollisionType type, Player* player = nullptr);
};