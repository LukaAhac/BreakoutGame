#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

struct BrickType;

class Brick : public sf::RectangleShape
{
private:
    char id;
    int  hp;

public:
    Brick(char id, int hp, sf::Vector2f size, sf::Texture* txPtr);

    char getId()
    {
        return id;
    }
    int getHp()
    {
        return hp;
    }

    void hit(std::map<char, BrickType*> idToType);
};