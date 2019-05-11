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
SpriteSheetAnimator<4, 1> animation {renderer, 64, 205, 50};

SDLTexture fooTexture = renderer.makeTexture();
SDLTexture backgroundTexture = renderer.makeTexture();

/*
static void rect_lerp(SDL_Rect *out, const SDL_Rect *start, const SDL_Rect *end, float f = 0) {
    float t = 1.0f - f;
    out->x = (float)start->x * t + (float)end->x * f;
    out->y = (float)start->y * t + (float)end->y * f;
}
*/

struct Clock {
    uint64_t now = SDL_GetPerformanceCounter();
    uint64_t last = 0;
    double elapsed = 0.0;
    double lag = 0.0;

    void tick() {
        last = now;
        now = SDL_GetPerformanceCounter();
        elapsed = (now - last) * 1000 / (double) SDL_GetPerformanceFrequency();
        lag += elapsed;
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
    SDLTexture texture = renderer.makeTexture();

    SDLSurface loadedSurface;
    loadedSurface.loadPNG(path);
    if ( loadedSurface.isLoaded() ) {
        loadedSurface.setKeyColor(SDL_TRUE, SDL_MapRGB( loadedSurface.pixelFormat(), 0, 0xFF, 0xFF ));
        texture.load(loadedSurface);
    }

    return texture;
}

SDLTexture loadTextTexture(std::string path, SDL_Color textColor) {
    SDLTexture texture = renderer.makeTexture();

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

        renderer = window.getRenderer(-1, SDL_RENDERER_ACCELERATED);
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

    if (man.moveDirection == 1) {
        man.x += 1;
        animation.flipHorizontal();
        animation.run();
    } else if (man.moveDirection == -1) {
        man.x -= 1;
        animation.unflip();
        animation.run();
    } else {
        animation.gotoFrame(0);
        animation.stop();
    }

    animation.tick();
}

void render() {
    backgroundTexture.render();
    animation.render(man.x, man.y);
    renderer.updateScreen();
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

const double MS_PER_UPDATE = 2.0; 
    // how much time the update step has been given (in ms)
    // this parameter has to be minimized, but if it is too small
    // then the game update (physics, AI, etc) will never catch up.

int WinMain() {


    if ( init() && load() ) {
        while ( globals.is_playing ) {

            clock.tick();
            handleInput();

            while ( clock.lag >= MS_PER_UPDATE) {
                update();
                clock.lag -= MS_PER_UPDATE;
            }

            /*TODO
            implement some kind of extrapolation between the
            the such that the fixed deltatime simulation of the
            update method and the rendering, such that animations 
            appear smoother. The lag / MS_PER_UPDATE ratio marks 
            how far we are into the next frame. [0,1)
            */

            render();
        }
    }

    return 0;
}
