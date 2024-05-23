#ifndef game_object_h
#define game_object_h

#include "total.h"
#include "bird.h"
#include "pipe.h"
class GameObject {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture_me;
    SDL_Texture* texture_back_intro;
    SDL_Texture* texture_button;
    SDL_Texture* texture_game_mode;
    SDL_Texture* texture_background;
    SDL_Texture* texture_bird;
    SDL_Texture* texture_gameOver;
    SDL_Texture* texture_playAgain;
    SDL_Texture* texture_yes;
    SDL_Texture* texture_no;
    SDL_Texture* texture_name;
    SDL_Texture* text_score;
    SDL_Texture* text_return_score;
    SDL_Texture* text_your_score;
    SDL_Texture* text_tutorial;
    Bird bird;
    Pipe* pipes[4];
    SDL_Rect rect_score;
    GameState cur_state = GameState::Intro;
    Mix_Music* music;
    Mix_Chunk* chunk_jump;
    Mix_Chunk* chunk_game_over;
    Mix_Chunk* chunk_mark;
    bool check_render_background = false;
    bool check_render_bird = false;
    bool check_render_gameOver = false;
    bool check_render_gameMode = false;
    int game_mode = 1;
    int mark;
public:
    SDL_Renderer getRenderer();
    void init();
    void running();
    void Intro();
    void GameMode();
    void Play();
    void GameOver();
    void Quit();
    ~GameObject();
};
#endif /* game_object_h */
