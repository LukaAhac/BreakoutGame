#include "Brick.h"

#include "Level.h"
#include "Constants.h"

Brick::Brick(char id, int hp, sf::Vector2f size, sf::Texture* txPtr)
    : id(id)
    , hp(hp)
    , sf::RectangleShape(size)
{
    setTexture(txPtr);
}

void Brick::hit(std::map<char, BrickType*> idToType)
{
    if (hp != UNNBREAKABLE_BRICK_HP)
    {
        hp--;
    }

    if (hp == 0)
    {
        idToType[id]->breakSound.play();
    }
    else
    {
        idToType[id]->hitSound.play();
    }
}