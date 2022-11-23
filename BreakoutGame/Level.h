#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <map>

struct BrickType
{
    sf::Texture     texture;
    int             hitPoints = 0;
    sf::SoundBuffer hitSoundBuff;
    sf::Sound       hitSound;
    sf::SoundBuffer breakSoundBuff;
    sf::Sound       breakSound;
    int             breakScore = 0;
};

class Level
{
private:
    int                        rowCount      = 0;
    int                        columnCount   = 0;
    int                        rowSpacing    = 0;
    int                        columnSpacing = 0;
    sf::Texture                backgroundTexture;
    sf::RectangleShape         background;
    std::string                bricksLayout;
    std::map<char, BrickType*> idToType;

public:
    ~Level();
    void loadLevel(std::string xmlFilePath);

    friend class GameScene;
};