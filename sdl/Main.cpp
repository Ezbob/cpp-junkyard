#include "SDL2/SDL.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int WinMain() {
    SDL_Window *window = nullptr;
    SDL_Surface *screenSurface = nullptr;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cerr << "Error: SDL could not be initialized: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow( 
            "SDL tut",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_WIDTH,
            SDL_WINDOW_SHOWN
        );

        if (window == nullptr) {
            std::cerr << "Error: Window could not be initialize: " << SDL_GetError() << std::endl;
        }  else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(window);

            SDL_Delay(2000);
            SDL_DestroyWindow(window);
        }
    }

    SDL_Quit();

    return 0;
}