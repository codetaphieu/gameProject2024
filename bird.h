#ifndef bird_h
#define bird_h

#include "def.h"
#include "pipe.h"
#include <SDL2/SDL.h>
class Bird {
public:
    SDL_Rect rect;
    double acelleration;
    double speed;
    Bird();
    void jump();
    void force();
};

#endif /* bird_h */
