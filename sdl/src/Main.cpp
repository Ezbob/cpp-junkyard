#include "SDL.hpp"
#include "Animator.hpp"
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 480;

SDLGlobals globals;
SDLWindow window;
SDLRenderer renderer;

SDL_Event event;
SpriteSheetAnimator<4, 1> animation {renderer, 64, 205};

SDLTexture fooTexture(renderer);
SDLTexture backgroundTexture(renderer);

/*
static void rect_lerp(SDL_Rect *out, const SDL_Rect *start, const SDL_Rect *end, float f = 0) {
    float t = 1.0f - f;
    out->x = (float)start->x * t + (float)end->x * f;
    out->y = (float)start->y * t + (float)end->y * f;
}
*/

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
    double y = 250;
    double speed = 0;
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
    SDLTexture texture(renderer);

    SDLSurface loadedSurface;
    loadedSurface.loadPNG(path);
    if ( loadedSurface.isLoaded() ) {
        loadedSurface.setKeyColor(SDL_TRUE, SDL_MapRGB( loadedSurface.pixelFormat(), 0, 0xFF, 0xFF ));
        texture.load(loadedSurface);
    }

    return texture;
}

SDLTexture loadTextTexture(std::string path, SDL_Color textColor) {

    SDLTexture texture(renderer);

    

    return texture;
}


bool init() {
    bool result = true;

    if ( globals.init(SDL_INIT_VIDEO | SDL_INIT_TIMER) ) {
        globals.loadExternLib(SDLExternLibs::SDL_IMAGE, IMG_INIT_PNG);
        globals.loadExternLib(SDLExternLibs::SDL_TTF);
        window.loadWindow("SDL Tutorial", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        renderer.load(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        renderer.setColor(0xFF, 0xFF, 0xFF, 0xFF);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // basically the anti-aliasing
    }

    result = globals.is_initialized && window.isLoaded();

    return result;
}

bool load() {

    fooTexture = loadTexture("assets/foo.png");

    if ( fooTexture.isLoaded() ) {
        animation.load(fooTexture);
        animation.run();
    }

    backgroundTexture = loadTexture("assets/landscape.png");

    return fooTexture.isLoaded();
}

void update() {

    backgroundTexture.render();

    animation.render(man.x, man.y);

    if (man.moveDirection != 0) {
        man.speed += 0.3 * clock.deltaTime;
    } else {
        man.speed -= 0.1 * clock.deltaTime;
    }

    if (man.speed < 0.0f) {
        man.speed = 0.0f;
    } else if ( man.speed >= 1.0f ) {
        man.speed = 1.0f;
    }

    if (man.moveDirection == 1) {
        man.x += man.speed;
        animation.flipHorizontal();
        animation.run();
    } else if (man.moveDirection == -1) {
        man.x -= man.speed;
        animation.unflip();
        animation.run();
    } else {
        animation.gotoFrame(0);
        animation.stop();
    }

    renderer.updateScreen();

    animation.tick();
}

void handleInput() {
    while ( SDL_PollEvent(&event) != 0 ) {
        if ( event.type == SDL_QUIT ) {
            globals.is_playing = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    man.moveDirection = -1;
                    break;
                case SDLK_RIGHT:
                    man.moveDirection = 1;
                    break;
                default:
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    man.moveDirection = 0;
                    break;
                default:
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
