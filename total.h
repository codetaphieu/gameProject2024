#ifndef total_h
#define total_h

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "def.h"
using namespace std;

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void logSDLError(ostream& os, const string& msg, bool fatal = false);
void waitUntilKeyPressed();

TTF_Font* loadFont(string font_path);
SDL_Texture* loadText(string text, string font_path, int x, SDL_Renderer* renderer);
SDL_Texture* loadImage(string path, SDL_Renderer* renderer);
void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer);
Mix_Chunk* loadChunk(std::string audioPath);
void playChunk(Mix_Chunk* sound);

bool isCollision(const SDL_Rect a, const SDL_Rect b, const SDL_Rect c);
bool isCollision_window(const SDL_Rect a);
Mix_Music* loadMusic(const char* path);
void playMusic(Mix_Music* gMusic);

#endif /* total_h */
