#include "SDL.hpp"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int WinMain() {
    SDLGlobals globals;

    if ( globals.init( SDL_INIT_VIDEO ) ) {
        SDLWindow window {"SDL2 tutorial", SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};

        if ( window != nullptr ) {
            SDLSurface screenSurface = window.getSurface();
            screenSurface.fill(0xF1, 0xF1, 0xF1);

            window.updateScreen();

        }

        SDLWindow window2 {"SDL22 tutorial", 20, SCREEN_WIDTH, SCREEN_HEIGHT};

        if ( window2 != nullptr ) {
            SDLSurface screenSurface = window2.getSurface();
            screenSurface.fill(0x11, 0xFF, 0xFF);

            window2.updateScreen();

        }

        SDL_Delay(2000);
    }

    return 0;
}