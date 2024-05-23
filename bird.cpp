#include "bird.h"
#include "pipe.h"
Bird::Bird() {
    rect.x = 200;
    rect.y = 150;
    rect.h = rect.w = 60;
}

void Bird::jump() {
    if (speed > 0) speed = -4.5;
    else speed -= 4.5;
}

void Bird::force() {
    speed += acelleration;
    rect.y += speed;
}

