#include "SDL.hpp"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool isPlaying = true;

namespace KeySurfaces {
    enum key {
        DEFAULT = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        TOTAL
    };
}

SDLGlobals globals;
SDLWindow window;
SDLRenderer renderer;
SDLTexture imageTexture;

SDL_Event event;
//SDLSurface keyPressSurfaces[KeySurfaces::TOTAL];

//KeySurfaces::key currentImage;

SDLSurface loadSurface(std::string path) {
    SDLSurface image;
    image.loadPNG(path);

    bool isLoaded = image.isLoaded();
    if ( isLoaded ) {
        image.convertToFormat(window.getSurface());
    }

    return image;
}

SDLTexture loadTexture(std::string path) {
    SDLTexture texture;

    SDLSurface loadedSurface;
    loadedSurface.loadPNG(path);
    if ( loadedSurface.isLoaded() ) {
        texture.load(SDL_CreateTextureFromSurface((SDL_Renderer *)renderer, (SDL_Surface *)loadedSurface));
    }

    return texture;
}

bool init() {
    bool result = true;

    if ( globals.init(SDL_INIT_VIDEO) ) {
        globals.loadExternLib(SDLExternLibs::SDL_IMAGE, IMG_INIT_PNG);
        window.loadWindow("SDL Tutorial", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        renderer.load((SDL_Window *) window, -1, SDL_RENDERER_ACCELERATED);
        renderer.setColor(0xFF, 0xFF, 0xFF, 0xFF);
    }

    result = globals.is_initialized && window.isLoaded();

    return result;
}

bool load() {
    bool result = true;

/*
    imageTexture = loadTexture("assets/helloworld.png");
    result = imageTexture.isLoaded();

    keyPressSurfaces[KeySurfaces::DEFAULT] = loadSurface("assets/helloworld.png");
    result = result && keyPressSurfaces[KeySurfaces::DEFAULT].isLoaded();

    keyPressSurfaces[KeySurfaces::UP] = loadSurface("assets/up.png");
    result = result && keyPressSurfaces[KeySurfaces::UP].isLoaded();

    keyPressSurfaces[KeySurfaces::DOWN] = loadSurface("assets/down.png");
    result = result && keyPressSurfaces[KeySurfaces::DOWN].isLoaded();

    keyPressSurfaces[KeySurfaces::LEFT] = loadSurface("assets/left.png");
    result = result && keyPressSurfaces[KeySurfaces::LEFT].isLoaded();

    keyPressSurfaces[KeySurfaces::RIGHT] = loadSurface("assets/right.png");
    result = result && keyPressSurfaces[KeySurfaces::RIGHT].isLoaded();
*/
    return result;
}

void update() {
    //SDLSurface screenSurface = window.getSurface();
    //SDLSurface currentSurface = keyPressSurfaces[currentImage];

    //SDL_BlitSurface((SDL_Surface *) currentSurface, nullptr, (SDL_Surface *) screenSurface, nullptr);
    renderer.setColor(0xFF, 0xFF, 0xFF);
    renderer.clear();
    //renderer.copyTexture(imageTexture);

    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    renderer.setColor(0xFF, 0x00, 0x00);
    renderer.fillRect(fillRect);
    renderer.setColor(0x00, 0xFF, 0x00);
    fillRect.x += 20;
    fillRect.y += 20;
    fillRect.w += 20;
    fillRect.h += 20;
    renderer.fillRect(fillRect);
    renderer.updateScreen();

    //window.updateScreen();
}

void handleInput() {
    while ( SDL_PollEvent(&event) != 0 ) {
        if (event.type == SDL_QUIT) {
            isPlaying = false;
        }
        /*else if (event.type == SDL_KEYDOWN) {
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
        */
    }
}

int WinMain() {

    if ( init() && load() ) {
        while ( isPlaying ) {
            handleInput();
            update();
        }
    }

    return 0;
}