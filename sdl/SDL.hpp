#ifndef SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3
#define SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <cstddef>
#include <memory>

namespace SDLExternLibs {
    enum lib {
        SDL_IMAGE = 1,
    };
}

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

    bool loadExternLib(SDLExternLibs::lib libsChosen, uint32_t libFlags = 0) {

        switch (libsChosen) {
            case SDLExternLibs::SDL_IMAGE:
                if ( !( IMG_Init(libFlags) & libFlags ) ) { // IMG_Init returns the flags set
                    std::cerr << "Error: Could not initialize SDL_Image: " << IMG_GetError() << std::endl;
                } else {
                    is_initialized = is_initialized && true;
                }
                break;
            
            default:
                break;
        }

        if (is_initialized)
            m_libs_set |= libsChosen;

        return is_initialized;
    }

    ~SDLGlobals() {
        SDL_Quit();

        if ( (m_libs_set & SDLExternLibs::SDL_IMAGE) == SDLExternLibs::SDL_IMAGE ) {
            IMG_Quit();
        }
    }

    uint32_t m_libs_set = 0;
    uint32_t m_flags_set = 0;
    bool is_initialized = false;
};

class SDLSurface;

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

    operator const SDL_Window *const() const {
        return m_window;
    }

    explicit operator SDL_Window *() const {
        return m_window;
    }

    void load(SDL_Window *wind);
    bool isLoaded();
    SDLSurface getSurface() const;
    bool updateScreen();

private:
    SDL_Window *m_window;
};


class SDLSurface {

public:
    SDLSurface(SDL_Surface *surface) {
        m_surface = std::shared_ptr<SDL_Surface>(surface, SDL_FreeSurface);
    }

    SDLSurface() {}

    operator const SDL_Surface *() const {
        return m_surface.get();
    }

    explicit operator SDL_Surface *() const {
        return m_surface.get();
    }

    bool isLoaded() const {
        return m_surface != nullptr;
    }

    void load(SDL_Surface *suf);
    void loadBMP(std::string filename);
    void loadPNG(std::string filename);

    /**
     * Convert the internal surface pixel format to the other surface's pixelformat
     */
    void convertToFormat(const SDLSurface &other);

    const SDL_PixelFormat *pixelFormat() const;
    void fill(int r, int g, int b);
    uint32_t rgbColor(int r, int g, int b) const;

private:
    std::shared_ptr<SDL_Surface> m_surface;
};

// surface impl -------------------------------------------------------------------------------------

void SDLSurface::load(SDL_Surface *suf) {
    m_surface = std::shared_ptr<SDL_Surface>(suf, SDL_FreeSurface);

    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
    }
}

void SDLSurface::loadBMP(std::string filename) {
    m_surface = std::shared_ptr<SDL_Surface>(SDL_LoadBMP(filename.c_str()), SDL_FreeSurface);

    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
    }
}

void SDLSurface::loadPNG(std::string filename) {
    m_surface = std::shared_ptr<SDL_Surface>(IMG_Load(filename.c_str()), SDL_FreeSurface);

    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
    }
}

void SDLSurface::convertToFormat(const SDLSurface &other) {

    std::shared_ptr<SDL_Surface> optimizedSurface = nullptr;
    optimizedSurface = std::shared_ptr<SDL_Surface>(SDL_ConvertSurface(m_surface.get(), other.pixelFormat(), 0), SDL_FreeSurface);
    if (optimizedSurface == nullptr) {
        std::cerr << "Error: Surface replace could not be initialized; convertion failed" << std::endl;
    } else {
        m_surface.swap(optimizedSurface);
        m_surface = optimizedSurface;
    }
}

const SDL_PixelFormat *SDLSurface::pixelFormat() const {
    return m_surface->format;
}

void SDLSurface::fill(int r, int g, int b) {
    SDL_FillRect(m_surface.get(), nullptr, rgbColor(r, g, b));
}

uint32_t SDLSurface::rgbColor(int r, int g, int b) const {
    const SDL_PixelFormat *mapper = pixelFormat();
    return SDL_MapRGB(mapper, r, g, b);
}

// Window impl -------------------------------------------------------------------------------------

void SDLWindow::load(SDL_Window *wind) {
    m_window = wind;
    if (m_window == nullptr) {
        std::cerr << "Error: Window could not be initialize: " << SDL_GetError() << std::endl;
    }
}

SDLSurface SDLWindow::getSurface() const {
    return SDLSurface(SDL_GetWindowSurface(m_window));
}

bool SDLWindow::updateScreen() {
    return SDL_UpdateWindowSurface(m_window) == 0;
}

bool SDLWindow::isLoaded() {
    return m_window != nullptr;
}

#endif