#include <iostream>
#include <SDL.h>

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 720;
const int BLOCK_SIZE = 50;
const float GRAVITY = 0.5f;
int red = 255;
int green = 0;
int blue = 0;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Jumping Blocks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect block1;
    block1.w = BLOCK_SIZE / 2;
    block1.h = BLOCK_SIZE / 2;
    block1.x = 50;
    block1.y = 400;

    SDL_Rect block2;
    block2.w = BLOCK_SIZE;
    block2.h = BLOCK_SIZE;
    block2.x = 150;
    block2.y = 400;

    SDL_Rect block3;
    block3.w = BLOCK_SIZE;
    block3.h = BLOCK_SIZE;
    block3.x = 300;
    block3.y = 400;

    SDL_Rect block4;
    block4.w = BLOCK_SIZE;
    block4.h = BLOCK_SIZE;
    block4.x = 450;
    block4.y = 400;

    SDL_Rect block5;
    block5.w = BLOCK_SIZE;
    block5.h = BLOCK_SIZE;
    block5.x = 600;
    block5.y = 400;

    SDL_Rect block6;
    block6.w = BLOCK_SIZE;
    block6.h = BLOCK_SIZE;
    block6.x = 750;
    block6.y = 400;

    bool isJumping = false;
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) {
                    block1.y -= 5;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    block1.y += 5;
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    block1.x -= 5;
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    block1.x += 5;
                }
                if (event.key.keysym.sym == SDLK_r) {
                    red = 255;
                    green = 0;
                    blue = 0;
                }
                if (event.key.keysym.sym == SDLK_g) {
                    red = 0;
                    green = 255;
                    blue = 0;
                }
                if (event.key.keysym.sym == SDLK_b) {
                    red = 0;
                    green = 0;
                    blue = 255;
                }
            }
        }



        // Kolizja między blokiem 1 a blokiem 2
        if ((block1.x < block2.x + block2.w and block1.x + block1.w > block2.x)
            && (block1.y < block2.y + block2.h and block1.y + block1.h > block2.y)) {
            if (block1.x > block2.x)
                block1.x = block2.x + block2.w;
            else if (block1.x < block2.x)
                block1.x = block2.x - block1.w;
        }
        if ((block1.x < block3.x + block3.w and block1.x + block1.w > block3.x)
            && (block1.y < block3.y + block3.h and block1.y + block1.h > block3.y)) {
            if (block1.x > block3.x)
                block1.x = block3.x + block3.w;
            else if (block1.x < block3.x)
                block1.x = block3.x - block1.w;
        }
        if ((block1.x < block4.x + block4.w and block1.x + block1.w > block4.x)
            && (block1.y < block4.y + block4.h and block1.y + block1.h > block4.y)) {
            if (block1.x > block4.x)
                block1.x = block4.x + block4.w;
            else if (block1.x < block4.x)
                block1.x = block4.x - block1.w;

        }
        if ((block1.x < block5.x + block5.w and block1.x + block1.w > block5.x)
            && (block1.y < block5.y + block5.h and block1.y + block1.h > block5.y)) {
            if (block1.x > block5.x)
                block1.x = block5.x + block5.w;
            else if (block1.x < block5.x)
                block1.x = block5.x - block1.w;
        }
        if ((block1.x < block6.x + block6.w and block1.x + block1.w > block6.x)
            && (block1.y < block6.y + block6.h and block1.y + block1.h > block6.y)) {
            if (block1.x > block6.x)
                block1.x = block6.x + block6.w;
            else if (block1.x < block6.x)
                block1.x = block6.x - block1.w;
        }

        if (isJumping) {
            if (block1.y > WINDOW_HEIGHT - BLOCK_SIZE - 100) {
                block1.y -= 5; // Poruszaj blokiem 1 w górę
            }
            else {
                isJumping = false;
            }
        }
        else if (block1.y < WINDOW_HEIGHT - BLOCK_SIZE) {
            block1.y += GRAVITY; // Dodaj grawitację do opadania
        }

        if (block1.y >= WINDOW_HEIGHT - BLOCK_SIZE) {
            block1.y = WINDOW_HEIGHT - BLOCK_SIZE;
        }

        if (block1.x < 0) {
            block1.x = 0;
        }
        if (block1.x + BLOCK_SIZE > WINDOW_WIDTH) {
            block1.x = WINDOW_WIDTH - BLOCK_SIZE;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderFillRect(renderer, &block1);

        // Rysuj drugi blok
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Niebieski kolor
        SDL_RenderFillRect(renderer, &block2);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Niebieski kolor
        SDL_RenderFillRect(renderer, &block3);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Niebieski kolor
        SDL_RenderFillRect(renderer, &block4);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Niebieski kolor
        SDL_RenderFillRect(renderer, &block5);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Niebieski kolor
        SDL_RenderFillRect(renderer, &block6);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
