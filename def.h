#ifndef def_h
#define def_h

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 504;
//const char* WINDOW_TITLE = "FLAPPY BIRD";

const int posY[] = {180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350};
const int COUNT_Y = sizeof(posY) / sizeof(int);

enum class GameState {
    Intro,
    Select,
    GameMode,
    Play,
    GameOver,
    PlayAgain,
    Quit,
};

#endif /* def_h */
