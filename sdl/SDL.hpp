#ifndef SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3
#define SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3

#include "SDL2/SDL.h"
#include <iostream>
#include <cstddef>

struct SDLGlobals {

    bool init(uint32_t init_flags) {
        if ( SDL_Init( m_flags_set ) < 0 ) {
            std::cerr << "Error: SDL could not be initialized: " << SDL_GetError() << std::endl;
            is_initialized = false;
            return false;
        }
        m_flags_set = init_flags;
        is_initialized = true;
        return true;
    }

    ~SDLGlobals() {
        SDL_Quit();
    }

    uint32_t m_flags_set = 0;
    bool is_initialized = false; 
};

class SDLSurface {

public:
    SDLSurface(SDL_Surface *surface, bool has_owner) {
        m_surface = surface;
        m_has_owner = has_owner;
    }

    SDLSurface() {}

    ~SDLSurface() {
        if (!m_has_owner && m_surface != nullptr) {
            SDL_FreeSurface(m_surface);
        }
    }

    void load(SDL_Surface *suf) {
        m_surface = suf;

        if (m_surface == nullptr) {
            std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
        }
    }

    void loadBMP(const char *filename) {
        m_surface = SDL_LoadBMP(filename);

        if (m_surface == nullptr) {
            std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
        }
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
    bool m_has_owner = false;
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

    SDLWindow() {}

    ~SDLWindow() {
        if (m_window != nullptr) SDL_DestroyWindow(m_window);
    }

    operator const SDL_Window *() const {
        return m_window;
    }

    explicit operator SDL_Window *() const {
        return m_window;
    }

    void load(SDL_Window *wind) {
        m_window = wind;
        if (m_window == nullptr) {
            std::cerr << "Error: Window could not be initialize: " << SDL_GetError() << std::endl;
        }
    }

    SDLSurface getSurface() {
        return SDLSurface(SDL_GetWindowSurface(m_window), true);
    }

    bool updateScreen() {
        return SDL_UpdateWindowSurface(m_window) == 0;
    }

private:
    SDL_Window *m_window = nullptr;
};


#endif