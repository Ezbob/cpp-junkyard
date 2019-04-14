#include "SDL.hpp"
#include <iostream>

const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 480;

SDLGlobals globals;
SDLWindow window;
SDLRenderer renderer;
SDLTexture backgroundTexture;
SDLTexture manTexture;

SDL_Event event;

struct Man {
    int x = 330;
    int y = 290;
} man;

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
        loadedSurface.setKeyColor(SDL_TRUE, SDL_MapRGB( loadedSurface.pixelFormat(), 0, 0xFF, 0xFF ));
        texture.load(loadedSurface, renderer);
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

        renderer.load(window, -1, SDL_RENDERER_ACCELERATED);
        renderer.setColor(0xFF, 0xFF, 0xFF, 0xFF);
    }

    result = globals.is_initialized && window.isLoaded();

    return result;
}

bool load() {
    bool result = true;

    backgroundTexture = loadTexture("assets/landscape.png");
    manTexture = loadTexture("assets/man.png");

    return result;
}

void update() {
    renderer.setColor(0xFF, 0xFF, 0xFF);
    renderer.clear();

    backgroundTexture.render();

    manTexture.render(man.x, man.y);

    renderer.updateScreen();
}

void handleInput() {
    while ( SDL_PollEvent(&event) != 0 ) {
        if (event.type == SDL_QUIT) {
            globals.is_playing = false;
        } else if ( event.type == SDL_KEYDOWN ) {
            switch ( event.key.keysym.sym ) {
                case SDLK_LEFT:
                    man.x -= 10;
                    break;
                case SDLK_RIGHT:
                    man.x += 10;
                    break;
            }
        }
    }
}

int WinMain() {

    if ( init() && load() ) {
        while ( globals.is_playing ) {
            handleInput();
            update();
        }
    }

    return 0;
}