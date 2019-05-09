#ifndef HEADER_GUARD_aed9ee4c025f13329af83560b1a51946
#define HEADER_GUARD_aed9ee4c025f13329af83560b1a51946

#include "SDL.h"
#include <iostream>

constexpr int CheckSDLError(int success, const char *message) {
    if (success != 0) { 
            std::cerr << "Error: " << message << ": " << SDL_GetError() << std::endl; 
    } 
    return success == 0;
}

template<typename T>
constexpr T *CheckSDLNullError(T *returned, const char *message) {
    if (returned == nullptr) { 
        std::cerr << "Error: " << message << ": " << SDL_GetError() << std::endl; 
    }
    return returned;
}

#endif
