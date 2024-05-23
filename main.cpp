#include "game_object.h"
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
int main(int argc, char* argv[]) {
   
    GameObject game;
    game.init();
//    Mix_Music* mMusic = Mix_LoadMUS("back_music.mp3");
//    Mix_PlayMusic(mMusic, 0);
    playMusic(loadMusic("back_music.mp3"));
    game.running();
    game.~GameObject();
    return 0;
}

