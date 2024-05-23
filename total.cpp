#include "total.h"
const char* WINDOW_TITLE = "TOPTEP BIRD";
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(cout, "CreateWindow", true);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void logSDLError(ostream& os, const string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
//    Mix_CloseAudio();
    IMG_Quit();
//    TTF_Quit();
//    Mix_Quit();
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

SDL_Texture* loadImage(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cout << "Unable to load image " << path << "SDL_image Error: "
            << IMG_GetError() << endl;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            cout << "Unable to create texture from " << path << "SDL_Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

bool isCollision(const SDL_Rect a, const SDL_Rect b, const SDL_Rect c) {
    if ((a.x <= b.x + b.w && b.x < a.x + a.w && a.y <= b.y + b.h && b.y <= a.y + a.h) || (a.x <= c.x + c.w && c.x < a.x + a.w && a.y <= c.y + c.h && c.y <= a.y + a.h - 30)) {
        return true;
    }
    return false;
}
bool isCollision_window(const SDL_Rect a) {
    if ((a.y >= -10) && (a.y + a.h <= SCREEN_HEIGHT + 20)) {
        return false;
    }
    return true;
}

TTF_Font* loadFont(string font_path, int x) {
    if (TTF_Init() == -1) {
        cout << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        return nullptr;
    }
    TTF_Font* font = TTF_OpenFont(font_path.c_str(), x);
    if (font == nullptr) {
        cout << "Font is not available" << endl << TTF_GetError();
        TTF_Quit();
        return nullptr;
    }
    return font;
}

SDL_Texture* loadText(string text, string font_path, int x, SDL_Renderer* renderer) {
    TTF_Font* font = loadFont(font_path, x);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 64, 64, 64 });
    if (textSurface == nullptr) {
        cout << "Failed to render text surface: " << TTF_GetError() << endl;
        TTF_CloseFont(font);
        TTF_Quit();
        return nullptr;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        cout << "Failed to create texture from surface: " << SDL_GetError() << endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        return nullptr;
    }
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return textTexture;
}


Mix_Chunk* loadChunk(string audioPath) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return nullptr;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return nullptr;
    }

    Mix_Chunk* sound = Mix_LoadWAV(audioPath.c_str());
    if (sound == nullptr) {
        cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        return nullptr;
    }
    return sound;
}

void playChunk(Mix_Chunk* sound) {
    if (sound != nullptr) {
        Mix_PlayChannel(-1, sound, 0);
    }
}


Mix_Music* loadMusic(const char* path) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return nullptr;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return nullptr;
    }
    Mix_Music* gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_ERROR,
            "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}
void playMusic(Mix_Music* gMusic) {
    if (gMusic == nullptr) return;
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}
