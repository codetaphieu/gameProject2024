#ifndef pipe_h
#define pipe_h
#include <SDL2/SDL.h>
#include "total.h"
class Pipe {
    SDL_Texture *top_pipe, *bot_pipe;
    SDL_Rect rect_bot, rect_top;
public:
    //SDL_Renderer* renderer;
    
    
    Pipe (SDL_Renderer* renderer, int x, int y);
    ~Pipe();
    void render_pipe(SDL_Renderer* renderer);
    void scroll(int distance);
    SDL_Texture* get_top_pipe() {
        return top_pipe;
    }
    SDL_Texture* get_bot_pipe() {
        return bot_pipe;
    }
    SDL_Rect get_rect_bot() {
        return rect_bot;
    }
    SDL_Rect get_rect_top() {
        return rect_top;
    }
};

#endif /* pipe_h */
