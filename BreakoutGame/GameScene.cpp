#include "GameScene.h"

#include "Constants.h"
#include "MainMenuScene.h"

//Creates left top and right game boarder
void GameScene::createBoarder()
{
    const sf::Color boarderColor = sf::Color::Blue;

    sf::RectangleShape leftBoarder(sf::Vector2f(WINDOW_WIDTH * VERTICAL_BOARDER_WIDTH, WINDOW_HEIGHT - TOP_HUD));
    leftBoarder.setFillColor(boarderColor);
    leftBoarder.setPosition(WINDOW_WIDTH * LEFT_BOARDER_X, TOP_HUD);
    gameBoarder.push_back(leftBoarder);

    sf::RectangleShape rightBoarder(sf::Vector2f(WINDOW_WIDTH * VERTICAL_BOARDER_WIDTH, WINDOW_HEIGHT - TOP_HUD));
    rightBoarder.setFillColor(boarderColor);
    rightBoarder.setPosition(WINDOW_WIDTH * RIGHT_BOARDER_X, TOP_HUD);
    gameBoarder.push_back(rightBoarder);

    sf::RectangleShape topBoarder(
        sf::Vector2f(WINDOW_WIDTH * (RIGHT_BOARDER_X + VERTICAL_BOARDER_WIDTH - LEFT_BOARDER_X), WINDOW_WIDTH * HORIZONTAL_BOARDER_HEIGHT));
    topBoarder.setFillColor(boarderColor);
    topBoarder.setPosition(WINDOW_WIDTH * LEFT_BOARDER_X, TOP_HUD);
    gameBoarder.push_back(topBoarder);
}

//Creats game "ball"
void GameScene::createBall()
{
    ball = Ball(sf::Vector2f(BALL_SIZE, BALL_SIZE), BALL_VELOCITY, BOUNCE_RIGHT_45);
    ball.setFillColor(sf::Color::White);
    ball.spawn();
}

//Creates raft that the user controls
void GameScene::createRaft()
{
    player = Player(sf::Vector2f(RAFT_WIDTH, RAFT_HEIGHT));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(player.getSize().x / 2, 0);
    player.setPosition(WINDOW_WIDTH / 2.f, RAFT_POSITION_Y);
}

//Create labels
void GameScene::createLabels()
{
    font.loadFromFile(FONT_PATH);

    levelLabel.setFont(font);
    levelLabel.setString("Level");
    levelLabel.setCharacterSize(FONT_SIZE);
    sf::FloatRect levelLabelRect = levelLabel.getLocalBounds();
    levelLabel.setOrigin(levelLabelRect.left + levelLabelRect.width / 2, levelLabelRect.top + levelLabelRect.height / 2);
    levelLabel.setPosition(LEVEL_LABEL_X, LABELS_FIRST_ROW);
    levelLabel.setFillColor(sf::Color::Green);
    levelLabel.setStyle(sf::Text::Bold);

    levelAmount.setFont(font);
    levelAmount.setString(std::to_string(1));
    levelAmount.setCharacterSize(FONT_SIZE);
    sf::FloatRect levelAmountRect = levelAmount.getLocalBounds();
    levelAmount.setOrigin(levelAmountRect.left + levelAmountRect.width / 2, levelAmountRect.top + levelAmountRect.height / 2);
    levelAmount.setPosition(LEVEL_LABEL_X, LABELS_SECOND_ROW);
    levelAmount.setFillColor(sf::Color::Green);
    levelAmount.setStyle(sf::Text::Bold);

    scoreLabel.setFont(font);
    scoreLabel.setString("Score");
    scoreLabel.setCharacterSize(FONT_SIZE);
    sf::FloatRect scoreLabelRect = scoreLabel.getLocalBounds();
    scoreLabel.setOrigin(scoreLabelRect.left + scoreLabelRect.width / 2, scoreLabelRect.top + scoreLabelRect.height / 2);
    scoreLabel.setPosition(SCORE_LABEL_X, LABELS_FIRST_ROW);
    scoreLabel.setFillColor(sf::Color::Green);
    scoreLabel.setStyle(sf::Text::Bold);

    scoreAmount.setFont(font);
    scoreAmount.setString(std::to_string(player.getScore()));
    scoreAmount.setCharacterSize(FONT_SIZE);
    sf::FloatRect scoreAmountRect = scoreAmount.getLocalBounds();
    scoreAmount.setOrigin(scoreAmountRect.left + scoreAmountRect.width / 2, scoreAmountRect.top + scoreAmountRect.height / 2);
    scoreAmount.setPosition(SCORE_LABEL_X, LABELS_SECOND_ROW);
    scoreAmount.setFillColor(sf::Color::Green);
    scoreAmount.setStyle(sf::Text::Bold);

    livesLabel.setFont(font);
    livesLabel.setString("Lives");
    livesLabel.setCharacterSize(FONT_SIZE);
    sf::FloatRect livesLabelRect = livesLabel.getLocalBounds();
    livesLabel.setOrigin(scoreLabelRect.left + livesLabelRect.width / 2, livesLabelRect.top + livesLabelRect.height / 2);
    livesLabel.setPosition(LIVES_LABEL_X, LABELS_FIRST_ROW);
    livesLabel.setFillColor(sf::Color::Green);
    livesLabel.setStyle(sf::Text::Bold);

    livesAmount.setFont(font);
    livesAmount.setString(std::to_string(player.getLives()));
    livesAmount.setCharacterSize(FONT_SIZE);
    sf::FloatRect livesAmountRect = livesAmount.getLocalBounds();
    livesAmount.setOrigin(livesAmountRect.left + livesAmountRect.width / 2, livesAmountRect.top + livesAmountRect.height / 2);
    livesAmount.setPosition(LIVES_LABEL_X, LABELS_SECOND_ROW);
    livesAmount.setFillColor(sf::Color::Green);
    livesAmount.setStyle(sf::Text::Bold);
}

//Load sounds
void GameScene::loadSounds()
{
    wallHitSoundBuff.loadFromFile(WALL_HIT_SOUND_PATH);
    wallHitSound.setBuffer(wallHitSoundBuff);

    raftHitSoundBuff.loadFromFile(RAFT_HIT_SOUND_PATH);
    raftHitSound.setBuffer(raftHitSoundBuff);
}

//Creats a level loaded from a xml file
void GameScene::createLevel()
{
    level.loadLevel(LEVEL_DIRECTORY + std::to_string(currentLevel) + LEVEL_FILE_FORMAT);

    bricks.clear();
    int brickIndex = 0;

    //Calculate bricksWidth and first row position based on level defition
    float brickWidth        = (GAME_SCREEN_WIDTH - level.columnSpacing * (level.columnCount - 1)) / level.columnCount;
    float brickRowPositionY = GAME_SCREEN_HEIGHT_THIRD - (level.rowCount * BRICK_HEIGHT + (level.rowCount - 1) * level.rowSpacing) / 2.f;

    //Create bricks
    for (int rows = 0; rows < level.rowCount; rows++)
    {
        for (float brickX = LEFT_BOARDER_ABSOLUTE; brickX < RIGHT_BOARDER_ABSOLUTE; brickX += brickWidth + level.columnSpacing)
        {
            char brickID = level.bricksLayout[brickIndex];
            //No brick check
            if (brickID == NO_BRICK_CHAR)
            {
                brickIndex++;
                continue;
            }
            Brick brick(brickID, level.idToType[brickID]->hitPoints, sf::Vector2f(brickWidth, BRICK_HEIGHT), &level.idToType[brickID]->texture);
            brickIndex++;
            brick.setPosition(brickX, brickRowPositionY);

            bricks.push_back(brick);
        }
        brickRowPositionY += BRICK_HEIGHT + level.columnSpacing;
    }

    //Calculate winConditionBrickLeft
    winConditionBricksLeft = 0;

    for (Brick& brick : bricks)
    {
        if (brick.getHp() == UNNBREAKABLE_BRICK_HP)
        {
            winConditionBricksLeft++;
        }
    }

    ball.spawn();
}

//Claculates euclidean distance betwen two points
double GameScene::calcDistance(sf::Vector2f p1, sf::Vector2f p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

//Test collision with given brick
void GameScene::horizontalBrickCollisonCheck(float k, float b, float y, Brick* brick)
{
    //Calculate collision position with given brick height y
    float x = (y - b) / k;

    //Test if collision is valid
    if (x >= (brick->getPosition().x - ball.getSize().x) && x <= (brick->getPosition().x + brick->getSize().x))
    {
        //More than one collision test
        double colDist = calcDistance(ball.getPosition(), sf::Vector2f(x, y));
        if (abs(colDist - collisionDistance) < DIFF)
        {
            collidingBricks.push_back(brick);
        }
        //New best collision test
        else if (colDist < collisionDistance)
        {
            collisionDistance = colDist;
            collisionX        = x;
            collisionY        = y;
            collidingBricks.clear();
            collidingBricks.push_back(brick);
        }
    }
}

//Calculate next horizontal brick collisions
void GameScene::calculateNextBrickCollision()
{
    collisionDistance = DBL_MAX;

    float k = (float)tan(ball.getAngle());

    //Top collision
    if (ball.goingUp())
    {
        float b = ball.getPosition().y - k * ball.getPosition().x;

        for (Brick& brick : bricks)
        {
            float y = brick.getPosition().y + brick.getSize().y;
            if (y <= ball.getPosition().y)
            {
                horizontalBrickCollisonCheck(k, b, y, &brick);
            }
        }
    }
    //Bottom collision
    else
    {
        float b = (ball.getPosition().y + ball.getSize().y) - k * ball.getPosition().x;

        for (Brick& brick : bricks)
        {
            float y = brick.getPosition().y;
            if (y >= ball.getPosition().y)
            {
                horizontalBrickCollisonCheck(k, b, y, &brick);
            }
        }
    }
}

//Create all scene elements
void GameScene::loadScene()
{
    createBoarder();
    createBall();
    createRaft();
    createLevel();
    createLabels();
    loadSounds();

    //Clculate first collision
    calculateNextBrickCollision();
    //Restart clock to render first frame properly
    clock->restart();
}

//Update bricks and score after collision
void GameScene::bricksUpdate()
{
    for (auto& brick : collidingBricks)
    {
        brick->hit(level.idToType);
    }
    collidingBricks.clear();

    auto it = bricks.begin();
    while (it != bricks.end())
    {
        if ((*it).getHp() == 0)
        {
            player.updateScore(level.idToType[(*it).getId()]->breakScore);
            it = bricks.erase(it);
        }
        else
        {
            it++;
        }
    }
    scoreAmount.setString(std::to_string(player.getScore()));
    sf::FloatRect scoreAmountRect = scoreAmount.getLocalBounds();
    scoreAmount.setOrigin(scoreAmountRect.left + scoreAmountRect.width / 2, scoreAmountRect.top + scoreAmountRect.height / 2);
    scoreAmount.setPosition(SCORE_LABEL_X, LABELS_SECOND_ROW);
}

//Check for boarder collisions
void GameScene::checkBoarderCollisions()
{
    sf::RectangleShape leftBoarder  = gameBoarder[0];
    sf::RectangleShape rightBoarder = gameBoarder[1];
    sf::RectangleShape topBoarder   = gameBoarder[2];
    //Left boarder
    if (ball.goingLeft() && ball.getPosition().x <= (leftBoarder.getPosition().x + leftBoarder.getSize().x))
    {
        ball.setPosition(leftBoarder.getPosition().x + leftBoarder.getSize().x, ball.getPosition().y);
        ball.updateAngle(CollisionType::Left);
        wallHitSound.play();
        calculateNextBrickCollision();
    }
    //Right boarder
    else if (!ball.goingLeft() && ball.getPosition().x + ball.getSize().x >= rightBoarder.getPosition().x)
    {
        ball.setPosition(rightBoarder.getPosition().x - ball.getSize().x, ball.getPosition().y);
        ball.updateAngle(CollisionType::Right);
        wallHitSound.play();
        calculateNextBrickCollision();
    }
    //Top boarder
    else if (ball.goingUp() && ball.getPosition().y <= topBoarder.getPosition().y + topBoarder.getSize().y)
    {
        ball.setPosition(ball.getPosition().x, topBoarder.getPosition().y + topBoarder.getSize().y);
        ball.updateAngle((CollisionType::Top));
        wallHitSound.play();
        calculateNextBrickCollision();
    }
}

//Check for raft collisions
void GameScene::checkRaftCollision()
{
    if (!ball.goingUp() && ball.getPosition().y + ball.getSize().y >= player.getPosition().y)
    {
        //Ball caught with raft
        if ((ball.getPosition().x + ball.getSize().x) >= (player.getPosition().x - player.getSize().x / 2) &&
            ball.getPosition().x <= (player.getPosition().x + player.getSize().x / 2))
        {
            ball.setPosition(ball.getPosition().x, player.getPosition().y - ball.getSize().y);
            ball.updateAngle(CollisionType::Raft, &player);
            raftHitSound.play();
            calculateNextBrickCollision();
        }
        //Ball fallen under raft
        else
        {
            player.decreaseLives();
            livesAmount.setString(std::to_string(player.getLives()));
            ball.spawn();
            ball.setAngle(BOUNCE_RIGHT_45);
        }
    }
}

//Check for brick collisions
void GameScene::checkBrickCollisions()
{
    if (collidingBricks.size() > 0)
    {
        if (ball.goingUp())
        {
            if (ball.getPosition().y <= collisionY)
            {
                ball.setPosition(ball.getPosition().x, collisionY);

                ball.updateAngle((CollisionType::Top));
                bricksUpdate();
            }
        }
        else
        {
            if (ball.getPosition().y + ball.getSize().y >= collisionY)
            {
                ball.setPosition(ball.getPosition().x, collisionY - ball.getSize().y);

                ball.updateAngle(CollisionType::Bottom);
                bricksUpdate();
            }
        }
    }
}

void GameScene::processEvents()
{
    sf::Event event;

    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        else if (event.type == sf::Event::MouseMoved)
        {
            float newX = (float)event.mouseMove.x / window->getSize().x * WINDOW_WIDTH;

            if (newX < (LEFT_BOARDER_ABSOLUTE + player.getSize().x / 2))
            {
                newX = LEFT_BOARDER_ABSOLUTE + player.getSize().x / 2;
            }
            else if (newX > (RIGHT_BOARDER_ABSOLUTE - player.getSize().x / 2))
            {
                newX = RIGHT_BOARDER_ABSOLUTE - player.getSize().x / 2;
            }

            player.setPosition(newX, RAFT_POSITION_Y);
        }
    }
}

void GameScene::update()
{
    ball.move(clock->restart().asSeconds());

    checkBoarderCollisions();
    checkRaftCollision();

    //Check loss condition
    if (player.getLives() <= 0)
    {
        sm->changeScene(new MainMenuScene(window, clock, sm));
        return;
    }

    checkBrickCollisions();

    //Check win condition
    if (bricks.size() == winConditionBricksLeft)
    {
        if (currentLevel < NUMBER_OF_LEVELS)
        {
            currentLevel++;
            levelAmount.setString(std::to_string(currentLevel));
            createLevel();
        }
        else
        {
            sm->changeScene(new MainMenuScene(window, clock, sm));
            return;
        }
    }
}

void GameScene::draw()
{
    for (auto& boarder : gameBoarder)
    {
        window->draw(boarder);
    }

    for (auto& brick : bricks)
    {
        window->draw(brick);
    }

#ifdef _DEBUG

    for (auto& brick : bricks)
    {
        window->draw(brick);

        sf::Text tx;
        tx.setFont(font);
        tx.setPosition(brick.getPosition());
        tx.setString(std::to_string(brick.getHp()));
        tx.setCharacterSize(14);
        tx.setFillColor(sf::Color::Yellow);
        tx.setStyle(sf::Text::Bold);
        window->draw(tx);
    }
#endif

    window->draw(ball);
    window->draw(player);

    window->draw(levelLabel);
    window->draw(levelAmount);
    window->draw(scoreLabel);
    window->draw(scoreAmount);
    window->draw(livesLabel);
    window->draw(livesAmount);
}