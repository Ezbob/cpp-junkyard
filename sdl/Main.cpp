#include "SDL.hpp"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDLGlobals globals;
SDLSurface image;
SDLWindow window;

bool init() {
    globals.init(SDL_INIT_VIDEO);
    window.load(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));

    return globals.is_initialized && (window != nullptr);
}

bool load() {
    image.loadBMP("assets/helloworld.bmp");

    return (image != nullptr);
}

void update() {
    SDLSurface screenSurface = window.getSurface();

    SDL_BlitSurface((SDL_Surface *) image, nullptr, (SDL_Surface *) screenSurface, nullptr);

    window.updateScreen();
}

int WinMain() {

    if ( init() && load() ) {
        update();
        SDL_Delay(2000);
    }

    return 0;
}