#include "pugixml.hpp"

#include "Level.h"

#include "Constants.h"


Level::~Level()
{
    for (auto& mapPair : idToType)
    {
        delete mapPair.second;
    }
}

void Level::loadLevel(std::string xmlFilePath)
{
    //Clear last level
    for (auto& pair : idToType)
    {
        delete pair.second;
    }
    bricksLayout.clear();

    //Load level
    pugi::xml_document doc;
    if (!doc.load_file(xmlFilePath.c_str()))
    {
        throw(std::exception("Cannot load lvl xml file"));
    }
    pugi::xml_node levelNode = doc.child("Level");

    //Level data
    rowCount              = atoi(levelNode.attribute("RowCount").value());
    columnCount           = atoi(levelNode.attribute("ColumnCount").value());
    rowSpacing            = atoi(levelNode.attribute("RowSpacing").value());
    columnSpacing         = atoi(levelNode.attribute("ColumnSpacing").value());
    backgroundTexture.loadFromFile(levelNode.attribute("BackgroundTexture").value());

    //Types of brick
    pugi::xml_node brickTypesNode = levelNode.child("BrickTypes");
    auto           brickTypeNodes = brickTypesNode.children("BrickType");

    for (auto brickType = brickTypeNodes.begin(); brickType != brickTypeNodes.end(); brickType++)
    {
        BrickType*  newBrickType = new BrickType();
        std::string id           = brickType->attribute("Id").value();
        if (!newBrickType->texture.loadFromFile(brickType->attribute("Texture").value()))
        {
            throw(std::exception("Cannot load texture file"));
        }
        std::string brickHP = brickType->attribute("HitPoints").value();
        if (brickHP == "Infinite")
        {
            newBrickType->hitPoints = UNNBREAKABLE_BRICK_HP;
        }
        else
        {
            newBrickType->hitPoints = stoi(brickHP);
            newBrickType->breakSoundBuff.loadFromFile(brickType->attribute("BreakSound").value());
            newBrickType->breakSound.setBuffer(newBrickType->breakSoundBuff);
            newBrickType->breakScore = atoi(brickType->attribute("BreakScore").value());
        }
        newBrickType->hitSoundBuff.loadFromFile(brickType->attribute("HitSound").value());
        newBrickType->hitSound.setBuffer(newBrickType->hitSoundBuff);

        idToType[id[0]] = newBrickType;
    }

    //Brick layout
    pugi::xml_node bricksLayout    = levelNode.child("Bricks");
    std::string    bricksLayoutStr = bricksLayout.text().as_string();

    for (char c : bricksLayoutStr)
    {
        if (c != '\n' && c != '\t' && c != ' ')
        {
            this->bricksLayout.push_back(c);
        }
    }
}