#include "SDL.hpp"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDLGlobals globals;
SDLSurface image;
SDLWindow window;

SDL_Event event;

bool init() {
    globals.init(SDL_INIT_VIDEO);
    window.load(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));

    return globals.is_initialized && (window != nullptr);
}

bool load() {
    bool result = true;
    image.loadBMP("assets/helloworld.bmp");

    result = image != nullptr;
    if (result) {
        image.convertToScreenFormat(window);
    }

    return result;
}

void update() {
    SDLSurface screenSurface = window.getSurface();

    SDL_BlitSurface((SDL_Surface *) image, nullptr, (SDL_Surface *) screenSurface, nullptr);

    window.updateScreen();
}

int WinMain() {

    bool doNotQuit = true;

    if ( init() && load() ) {
        while ( doNotQuit ) {
            while ( SDL_PollEvent(&event) != 0 ) {
                if (event.type == SDL_QUIT) {
                    doNotQuit = false;
                }
            }

            update();
        }
    }

    return 0;
}