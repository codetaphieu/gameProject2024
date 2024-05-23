#include "pipe.h"
Pipe::Pipe(SDL_Renderer* renderer, int x, int y){
    top_pipe = loadImage("top.jpg", renderer);
    bot_pipe = loadImage("bot.jpg", renderer);
    rect_bot.x = rect_top.x = x;
    rect_bot.y = y;
    rect_top.y = - (345 - (y - 150));
    rect_bot.h = rect_top.h = 345;
    rect_bot.w = rect_top.w = 60;
}

void Pipe::scroll(int dis) {
    rect_bot.x -= dis;
    rect_top.x -= dis;
    if (rect_top.x < -100) {
        rect_top.x = 1100;
        rect_bot.x = 1100;
        rect_bot.y = posY[rand() % COUNT_Y];
        rect_top.y = - (345 - (rect_bot.y - 150));
    }
    
}

Pipe::~Pipe() {
    SDL_DestroyTexture(top_pipe);
    SDL_DestroyTexture(bot_pipe);
}

void Pipe::render_pipe(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, bot_pipe, NULL, &rect_bot);
    SDL_RenderCopy(renderer, top_pipe, NULL, &rect_top);
}
