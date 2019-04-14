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
        texture.load(renderer.createTextureFromSurface((SDL_Surface *) loadedSurface));
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

    imageTexture = loadTexture("assets/helloworld.png");

    return result;
}

void update() {
    renderer.setColor(0xFF, 0xFF, 0xFF);
    renderer.clear();

    SDL_Rect topLeftVp;
    topLeftVp.x = 0;
    topLeftVp.y = 0;
    topLeftVp.w = SCREEN_WIDTH / 2;
    topLeftVp.h = SCREEN_HEIGHT / 2;

    renderer.setViewPort(topLeftVp);

    renderer.copyTexture(imageTexture);

    SDL_Rect topRightVp;
    topRightVp.x = SCREEN_WIDTH / 2;
    topRightVp.y = 0;
    topRightVp.w = SCREEN_WIDTH / 2;
    topRightVp.h = SCREEN_HEIGHT / 2;

    renderer.setViewPort(topRightVp);

    renderer.copyTexture(imageTexture);

    SDL_Rect bottomVp;
    bottomVp.x = 0;
    bottomVp.y = SCREEN_HEIGHT / 2;
    bottomVp.w = SCREEN_WIDTH;
    bottomVp.h = SCREEN_HEIGHT / 2;

    renderer.setViewPort(bottomVp);

    renderer.copyTexture(imageTexture);

    renderer.updateScreen();
}

void handleInput() {
    while ( SDL_PollEvent(&event) != 0 ) {
        if (event.type == SDL_QUIT) {
            isPlaying = false;
        }
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