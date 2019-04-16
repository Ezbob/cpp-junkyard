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

static void rect_lerp(SDL_Rect *out, const SDL_Rect *start, const SDL_Rect *end, float f = 0) {
    float t = 1.0f - f;
    out->x = (float)start->x * t + (float)end->x * f;
    out->y = (float)start->y * t + (float)end->y * f;
}

struct Clock {
    uint64_t NOW = SDL_GetPerformanceCounter();
    uint64_t LAST = 0;
    double deltaTime = 0;

    void tick() {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (NOW - LAST) * 1000 / (double) SDL_GetPerformanceFrequency();
    }
} clock;


struct Man {
    double x = 330;
    double y = 290;
    int moveDirection = 0;
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

    if ( globals.init(SDL_INIT_VIDEO | SDL_INIT_TIMER) ) {
        globals.loadExternLib(SDLExternLibs::SDL_IMAGE, IMG_INIT_PNG);
        window.loadWindow("SDL Tutorial", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        renderer.load(window, -1, SDL_RENDERER_ACCELERATED);
        renderer.setColor(0xFF, 0xFF, 0xFF, 0xFF);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // basically the anti-aliasing
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

    if ( man.moveDirection > 0 ) {
        man.x += (1. * clock.deltaTime);
    } else if (man.moveDirection < 0) {
        man.x -= (1. * clock.deltaTime);
    }

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
                    man.moveDirection = -1;
                    break;
                case SDLK_RIGHT:
                    man.moveDirection = 1;
                    break;
            }
        } else if ( event.type == SDL_KEYUP ) {
            switch ( event.key.keysym.sym ) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    man.moveDirection = 0;
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

            clock.tick();
        }
    }

    return 0;
}