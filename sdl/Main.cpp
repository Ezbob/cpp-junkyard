#include "SDL.hpp"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

namespace KeySurfaces {
    enum key {
        DEFAULT = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        TOTAL
    } ;
}

SDLGlobals globals;
SDLWindow window;
SDL_Event event;

SDLSurface keyPressSurfaces[KeySurfaces::TOTAL];

KeySurfaces::key currentImage;

SDLSurface loadSurface(std::string path) {
    SDLSurface image;
    image.loadBMP(path);

    bool isLoaded = image.isLoaded();
    if ( isLoaded ) {
        image.convertToFormat(window.getSurface());
    }

    return image;
}

bool init() {
    globals.init(SDL_INIT_VIDEO);
    window.load(SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));

    return globals.is_initialized && (window != nullptr);
}

bool load() {
    bool result = true;

    keyPressSurfaces[KeySurfaces::DEFAULT] = loadSurface("assets/helloworld.bmp");
    result = result && keyPressSurfaces[KeySurfaces::DEFAULT].isLoaded();

    keyPressSurfaces[KeySurfaces::UP] = loadSurface("assets/up.bmp");
    result = result && keyPressSurfaces[KeySurfaces::UP].isLoaded();

    keyPressSurfaces[KeySurfaces::DOWN] = loadSurface("assets/down.bmp");
    result = result && keyPressSurfaces[KeySurfaces::DOWN].isLoaded();

    keyPressSurfaces[KeySurfaces::LEFT] = loadSurface("assets/left.bmp");
    result = result && keyPressSurfaces[KeySurfaces::LEFT].isLoaded();

    keyPressSurfaces[KeySurfaces::RIGHT] = loadSurface("assets/right.bmp");
    result = result && keyPressSurfaces[KeySurfaces::RIGHT].isLoaded();

    return result;
}

void update() {
    SDLSurface screenSurface = window.getSurface();
    SDLSurface currentSurface = keyPressSurfaces[currentImage];

    SDL_BlitSurface((SDL_Surface *) currentSurface, nullptr, (SDL_Surface *) screenSurface, nullptr);

    window.updateScreen();
}

int WinMain() {

    bool doNotQuit = true;

    if ( init() && load() ) {
        while ( doNotQuit ) {
            while ( SDL_PollEvent(&event) != 0 ) {
                if (event.type == SDL_QUIT) {
                    doNotQuit = false;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            currentImage = KeySurfaces::UP;
                            break;
                        case SDLK_DOWN:
                            currentImage = KeySurfaces::DOWN;
                            break;
                        case SDLK_LEFT:
                            currentImage = KeySurfaces::LEFT;
                            break;
                        case SDLK_RIGHT:
                            currentImage = KeySurfaces::RIGHT;
                            break;
                        default:
                            currentImage = KeySurfaces::DEFAULT;
                            break;
                    }
                }
            }

            update();
        }
    }

    return 0;
}