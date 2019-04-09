#ifndef SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3
#define SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3

#include "SDL2/SDL.h"
#include <iostream>
#include <cstddef>

struct SDLGlobals {

    bool init(uint32_t init_flags) {
        if ( SDL_Init( m_flags_set ) < 0 ) {
            std::cerr << "Error: SDL could not be initialized: " << SDL_GetError() << std::endl;
            return false;
        }
        m_flags_set = init_flags;
        return true;
    }

    ~SDLGlobals() {
        SDL_Quit();
    }

    uint32_t m_flags_set;
};

class SDLSurface {

public:
    SDLSurface(SDL_Surface *surface) {
        m_surface = surface;
    }

    operator const SDL_Surface *() const {
        return m_surface;
    }

    explicit operator SDL_Surface *() const {
        return m_surface;
    }

    const SDL_PixelFormat *pixelFormat() const {
        return m_surface->format;
    }

    void fill(int r, int g, int b) {
        SDL_FillRect(m_surface, nullptr, rgbColor(r, g, b));
    }

    uint32_t rgbColor(int r, int g, int b) const {
        const SDL_PixelFormat *mapper = pixelFormat();
        return SDL_MapRGB(mapper, r, g, b);
    }

private:
    SDL_Surface *m_surface = nullptr;
};


class SDLWindow {

public:
    SDLWindow(const char *title, int x, int y, int width, int height, uint32_t flags = SDL_WINDOW_SHOWN) {
        m_window = SDL_CreateWindow( 
            title, x, y, width, height, flags
        );
        if (m_window == nullptr) {
            std::cerr << "Error: Window could not be initialize: " << SDL_GetError() << std::endl;
        }
    }

    SDLWindow(const char *title, int xy, int width, int height, uint32_t flags = SDL_WINDOW_SHOWN) {
        m_window = SDL_CreateWindow( 
            title, xy, xy, width, height, flags
        );
        if (m_window == nullptr) {
            std::cerr << "Error: Window could not be initialize: " << SDL_GetError() << std::endl;
        }
    }

    ~SDLWindow() {
        SDL_DestroyWindow(m_window);
    }

    operator const SDL_Window *() const {
        return m_window;
    }

    explicit operator SDL_Window *() const {
        return m_window;
    }

    SDLSurface getSurface() {
        return SDLSurface(SDL_GetWindowSurface(m_window));
    }

    bool updateScreen() {
        return SDL_UpdateWindowSurface(m_window) == 0;
    }

private:
    SDL_Window *m_window = nullptr;
};


#endif