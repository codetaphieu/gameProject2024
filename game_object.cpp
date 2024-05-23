#include "game_object.h"
#include <iostream>

void GameObject::init() {
    initSDL(window, renderer);
}
SDL_Event event;
void GameObject::running() {
    while (cur_state != GameState::Quit) {
        Intro();
    }
}

void GameObject::Intro() {
    while (cur_state == GameState::Intro) {
        texture_name = loadImage("name_game.png", renderer);
        texture_back_intro = loadImage("back_intro.jpg", renderer);
        texture_button = loadImage("button.png", renderer);
        texture_me = loadImage("me.png", renderer);
        renderTexture(texture_back_intro, -245, 0, renderer);
        renderTexture(texture_name, 170, 30, renderer);
        renderTexture(texture_me, 275, 430, renderer);
        renderTexture(texture_button, 117, 100, renderer);
        SDL_RenderPresent(renderer);
        cur_state = GameState::Select;
    }
    while (cur_state == GameState::Select) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= (325) && x <= (590) && y >= (170) && y <= (170 + 80)) {
                        chunk_jump = loadChunk("jump.mp3");
                        playChunk(chunk_jump);
                        cur_state = GameState::Play;
                        Play();
                    } else if (x >= (325) && x <= (590) && y >= (170 + 80) && y <= (170 + 2 * 80)) {
                        chunk_jump = loadChunk("jump.mp3");
                        playChunk(chunk_jump);
                        cur_state = GameState::GameMode;
                        GameMode();
                    } else if (x >= (325) && x <= (590) && y >= (170 + 2 * 80) && y <= (170 + 3 * 80)) {
                        chunk_jump = loadChunk("jump.mp3");
                        playChunk(chunk_jump);
                        cur_state = GameState::Quit;
                        Quit();
                    }
            }
        }
    }
}

void GameObject::GameMode() {
    while (cur_state == GameState::GameMode) {
        texture_back_intro = loadImage("back_intro.jpg", renderer);
        texture_game_mode = loadImage("game_mode.png", renderer);
        renderTexture(texture_back_intro, -245, 0, renderer);
        renderTexture(texture_game_mode, 300, 125, renderer);
        SDL_RenderPresent(renderer);
        check_render_gameMode = true;
        cur_state = GameState::Select;
    }
    while (cur_state == GameState::Select) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= (300) && x <= (300 + 300) && y >= (125) && y <= (125 + 60)) {
                    chunk_jump = loadChunk("jump.mp3");
                    playChunk(chunk_jump);
                    game_mode = 1;
                    cur_state = GameState::Intro;
                    Intro();
                } else if (x >= 300 && x <= (300 + 300) && y >= (125 + 60 + 35) && y <= (125 + 60 + 35 + 60)) {
                    chunk_jump = loadChunk("jump.mp3");
                    playChunk(chunk_jump);
                    game_mode = 2;
                    cur_state = GameState::Intro;
                    Intro();
                } else if (x >= (300) && x <= (300 + 300) && y >= (125 + 60 + 35 + 60 + 35) && y <= (125 + 60 + 35 + 60 + 35 + 60)) {
                    chunk_jump = loadChunk("jump.mp3");
                    playChunk(chunk_jump);
                    game_mode = 3;
                    cur_state = GameState::Intro;
                    Intro();
                }
            }
        }
    }
}

void GameObject::Play() {
    mark = 0;
        srand((int)time(0));
        bird.rect.y = 150;
        texture_background = loadImage("background.png", renderer);
        texture_bird = loadImage("bird.png", renderer);
        for (int i = 0; i < 4; i++){
            pipes[i] = new Pipe(renderer, 1000 + i * 300, posY[rand() % COUNT_Y]);
        }
        
        //    SDL_Event event;
        bird.acelleration = 0.5;
        bird.speed = 0;
    if (cur_state == GameState::Play) {
        renderTexture(texture_background, 0, 0, renderer);
        renderTexture(texture_bird, bird.rect.x, bird.rect.y, renderer);
        text_score = loadText("0", "Atop-R99O3.ttf", 80, renderer);
        text_tutorial = loadText("press any key to play!!!", "HappyLucky-gxnZP.ttf", 30, renderer);
        renderTexture(text_score, 420, 50, renderer);
        renderTexture(text_tutorial, 100, 200, renderer);
        SDL_RenderPresent(renderer);
        check_render_background = check_render_bird = true;
    }
        waitUntilKeyPressed();
        SDL_DestroyTexture(text_tutorial);
        while (cur_state != GameState::Quit) {
            
            if (isCollision(bird.rect, pipes[0]->get_rect_top(), pipes[0]->get_rect_bot()) ||
                isCollision(bird.rect, pipes[1]->get_rect_top(), pipes[1]->get_rect_bot()) ||
                isCollision(bird.rect, pipes[2]->get_rect_top(), pipes[2]->get_rect_bot()) ||
                isCollision(bird.rect, pipes[3]->get_rect_top(), pipes[3]->get_rect_bot()) ||
                isCollision_window(bird.rect)) {
                cur_state = GameState::GameOver;
                GameOver();
                if (cur_state == GameState::Intro) {
                    Intro();
                }
                else if (cur_state == GameState::Play) {
                    Play();
                }
            }
            if (pipes[0]->get_rect_top().x + pipes[0]->get_rect_top().w == 200 ||
                pipes[1]->get_rect_top().x + pipes[1]->get_rect_top().w == 200 ||
                pipes[2]->get_rect_top().x + pipes[2]->get_rect_top().w == 200 ||
                pipes[3]->get_rect_top().x + pipes[3]->get_rect_top().w == 200) {
                mark++;
                chunk_mark = loadChunk("mark.mp3");
                playChunk(chunk_mark);
            }
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_KEYDOWN:
                    chunk_jump = loadChunk("jump.mp3");
                    playChunk(chunk_jump);
                     if (game_mode == 1 || game_mode == 2) bird.speed = -6;
                     else if (game_mode == 3) bird.speed = -8;
                    break;
                default:
                    break;
            }
            //background
            renderTexture(texture_background, 0, 0, renderer);
            //bird
            renderTexture(texture_bird, bird.rect.x, bird.rect.y, renderer);
            bird.force();
            //pipe
            for (int i = 0; i < 4; i++) {
                if (game_mode == 1) {
                    pipes[i]->scroll(4);
                } else if (game_mode == 2) {
                    pipes[i]->scroll(5);
                } else if (game_mode == 3) {
                    pipes[i]->scroll(5);
                }
                pipes[i]->render_pipe(renderer);
            }
            //score
            text_score = loadText(to_string(mark), "Atop-R99O3.ttf", 80, renderer);
            renderTexture(text_score, 420, 50, renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }
}


void GameObject::GameOver() {
    while (cur_state == GameState::GameOver) {
        chunk_game_over = loadChunk("game_over.mp3");
        playChunk(chunk_game_over);
        texture_gameOver = loadImage("gameOver.png", renderer);
        texture_playAgain = loadImage("play_again.png", renderer);
        texture_yes = loadImage("yes.png", renderer);
        texture_no = loadImage("no.png", renderer);
        text_your_score = loadText("score: ", "Atop-R99O3.ttf", 80, renderer);
        text_return_score = loadText(to_string(mark), "Atop-R99O3.ttf", 80, renderer);
        renderTexture(texture_gameOver, 300, 50, renderer);
        renderTexture(texture_playAgain, 320, 250, renderer);
        renderTexture(texture_yes, 340, 315, renderer);
        renderTexture(texture_no, 460, 315, renderer);
        renderTexture(text_your_score, 280, 380, renderer);
        renderTexture(text_return_score, 580, 380, renderer);
        SDL_RenderPresent(renderer);
        check_render_gameOver = true;
        cur_state = GameState::PlayAgain;
    }
    while (cur_state == GameState::PlayAgain) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= (345) && x <= (450) && y >= (320) && y <= (380)) {
                    cur_state = GameState::Play;
                } else if (x >= (470) && x <= (540) && y >= (320) && y <= (380)) {
                    cur_state = GameState::Intro;
                }
            }
        }
    }
}

void GameObject::Quit() {
    if (cur_state == GameState::Quit) {
        SDL_DestroyTexture(texture_back_intro);
        SDL_DestroyTexture(texture_button);
        if (check_render_bird == true)          SDL_DestroyTexture(texture_bird);
        if (check_render_gameMode == true)      SDL_DestroyTexture(texture_game_mode);
        if (check_render_background == true)    SDL_DestroyTexture(texture_background);
        if (check_render_gameOver == true)      SDL_DestroyTexture(texture_gameOver);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        quitSDL(window, renderer);
    }
}
GameObject::~GameObject() {
    SDL_DestroyTexture(texture_back_intro);
    SDL_DestroyTexture(texture_button);
    if (check_render_bird == true)          SDL_DestroyTexture(texture_bird);
    if (check_render_gameMode == true)      SDL_DestroyTexture(texture_game_mode);
    if (check_render_background == true)    SDL_DestroyTexture(texture_background);
    if (check_render_gameOver == true)      SDL_DestroyTexture(texture_gameOver);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    quitSDL(window, renderer);
};

