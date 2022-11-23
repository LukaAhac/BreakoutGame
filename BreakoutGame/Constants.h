#pragma once

//Window constants
constexpr int   WINDOW_WIDTH  = 800;
constexpr int   WINDOW_HEIGHT = 800;
constexpr float TOP_HUD       = 0.15 * WINDOW_HEIGHT;
constexpr int   FRAME_LIMIT   = 80;

//Boarder constants relative to the screen size
constexpr float VERTICAL_BOARDER_WIDTH    = 1.f / 20.f;
constexpr float LEFT_BOARDER_X            = 1.f / 20.f;
constexpr float RIGHT_BOARDER_X           = 18.f / 20.f;
constexpr float HORIZONTAL_BOARDER_HEIGHT = 1.f / 20.f;

//Absolute boarder coordinates
constexpr float LEFT_BOARDER_ABSOLUTE    = WINDOW_WIDTH * LEFT_BOARDER_X + WINDOW_WIDTH * VERTICAL_BOARDER_WIDTH;
constexpr float RIGHT_BOARDER_ABSOLUTE   = WINDOW_WIDTH * RIGHT_BOARDER_X;
constexpr float TOP_BOARDER_ABSOLUTE     = TOP_HUD + HORIZONTAL_BOARDER_HEIGHT * WINDOW_HEIGHT;
constexpr float GAME_SCREEN_WIDTH        = RIGHT_BOARDER_ABSOLUTE - LEFT_BOARDER_ABSOLUTE;
constexpr float GAME_SCREEN_HEIGHT       = WINDOW_HEIGHT - TOP_BOARDER_ABSOLUTE;
constexpr float GAME_SCREEN_HEIGHT_THIRD = TOP_BOARDER_ABSOLUTE + GAME_SCREEN_HEIGHT / 3.f;

//Player and raft constants
constexpr int   INNITIAL_LIVES    = 3;
constexpr int   INNITIAL_SCORE    = 0;
constexpr float RAFT_WIDTH        = 120.f;
constexpr float RAFT_HEIGHT       = 15.f;
constexpr float RAFT_POSITION_Y   = WINDOW_HEIGHT * 0.95;
constexpr float RAFT_BOUNCE_PARTS = RAFT_WIDTH / 6;

//Ball constants
constexpr float BALL_SIZE     = 10.f;
constexpr int   BALL_VELOCITY = 400;
constexpr float BALL_SPAWN_X  = WINDOW_WIDTH / 2.f;
constexpr float BALL_SPAWN_Y  = RAFT_POSITION_Y - BALL_SIZE - 10;

//Math constants
constexpr double PI       = 3.14159265358979323846;
constexpr double ANGLE0   = 0.;
constexpr double ANGLE45  = PI / 4.;
constexpr double ANGLE90  = PI / 2.;
constexpr double ANGLE180 = PI;
constexpr double ANGLE270 = 3. / 2. * PI;
constexpr double ANGLE360 = 2. * PI;

//Raft bounce angles
constexpr double BOUNCE_LEFT_30  = (180. + 30.) * PI / 180.;  //210 degree in radians
constexpr double BOUNCE_LEFT_45  = (180. + 45.) * PI / 180.;  //225 degree in radians
constexpr double BOUNCE_LEFT_60  = (180. + 60.) * PI / 180.;  //240 degree in radians
constexpr double BOUNCE_RIGHT_60 = (270. + 30) * PI / 180.;   //300 degree in radians
constexpr double BOUNCE_RIGHT_45 = (270. + 45.) * PI / 180.;  //315 degree in radians
constexpr double BOUNCE_RIGHT_30 = (270. + 60) * PI / 180.;   //330 degree in radians

//Brick constants
constexpr float BRICK_HEIGHT          = 15.f;
constexpr int   UNNBREAKABLE_BRICK_HP = -1;

//Welcome scene constants
const std::string WELCOME_IMAGE_PATH = "Assets\\Textures\\WelcomeScreen\\WelcomeScreen.png";
constexpr float   FADE_IN_TIME       = 2.f;
constexpr float   DISPLAY_TIME       = 3.f;
constexpr float   FADE_OUT_TIME      = 2.4f;

//MainMenu scene constants
const std::string PLAY_BUTTON_TEXTURE_PATH = "Assets\\Textures\\Buttons\\button_play.png";
const std::string QUIT_BUTTON_TEXTURE_PATH = "Assets\\Textures\\Buttons\\button_quit.png";
constexpr float   BUTTON_WIDTH             = WINDOW_WIDTH * 0.4;
constexpr float   BUTTON_HEIGHT            = WINDOW_HEIGHT * 0.05;
constexpr float   BUTTON_X                 = (WINDOW_WIDTH - BUTTON_WIDTH) / 2.f;
constexpr float   PLAY_BUTTON_Y            = WINDOW_HEIGHT * 0.4;
constexpr float   QUIT_BUTTON_Y            = WINDOW_HEIGHT * 0.6;

//Game scene constants
const std::string FONT_PATH           = "Assets\\Fonts\\arial.ttf";
const std::string WALL_HIT_SOUND_PATH = "Assets\\Sounds\\Hit.wav";
const std::string RAFT_HIT_SOUND_PATH = "Assets\\Sounds\\RaftHit.wav";
constexpr int     FONT_SIZE           = 25;
constexpr float   LEVEL_LABEL_X       = WINDOW_WIDTH / 4.f;
constexpr float   SCORE_LABEL_X       = WINDOW_WIDTH / 4.f * 2.f;
constexpr float   LIVES_LABEL_X       = WINDOW_WIDTH / 4.f * 3.f;
constexpr float   LABELS_FIRST_ROW    = TOP_HUD / 3.f;
constexpr float   LABELS_SECOND_ROW   = TOP_HUD / 3.f * 2.f;
constexpr double  DIFF                = 1;
constexpr char    NO_BRICK_CHAR       = '_';
constexpr int     NUMBER_OF_LEVELS    = 3;
const std::string LEVEL_DIRECTORY     = "Levels\\";
const std::string LEVEL_FILE_FORMAT   = ".xml";