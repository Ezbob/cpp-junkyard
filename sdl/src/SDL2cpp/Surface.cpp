#include <iostream>
#include "SDL_image.h"
#include "SDL2cpp/ErrorCheck.hpp"
#include "SDL2cpp/Surface.hpp"

SDLSurface::SDLSurface(SDL_Surface *surface) {
    m_surface = std::shared_ptr<SDL_Surface>(surface, SDL_FreeSurface);
    m_width = surface->w;
    m_height = surface->h;
}

SDLSurface::SDLSurface() {}

void SDLSurface::load(SDL_Surface *suf) {
    m_surface = std::shared_ptr<SDL_Surface>(suf, SDL_FreeSurface);
    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
        return;
    }
    m_height = m_surface->h;
    m_width = m_surface->w;
}

void SDLSurface::loadBMP(std::string filename) {
    m_surface = std::shared_ptr<SDL_Surface>(SDL_LoadBMP(filename.c_str()), SDL_FreeSurface);
    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
        return;
    }
    m_height = m_surface->h;
    m_width = m_surface->w;
}

void SDLSurface::loadPNG(std::string filename) {
    m_surface = std::shared_ptr<SDL_Surface>(IMG_Load(filename.c_str()), SDL_FreeSurface);
    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
        return;
    }
    m_height = m_surface->h;
    m_width = m_surface->w;
}

void SDLSurface::loadSolidText(std::string text, TTF_Font &font, SDL_Color color) {
    m_surface = std::shared_ptr<SDL_Surface>(TTF_RenderText_Solid(&font, text.c_str(), color));
    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << TTF_GetError() << std::endl;
        return;
    }
    m_height = m_surface->h;
    m_width = m_surface->w;
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

int SDLSurface::setKeyColor(int flags, uint32_t color) {
    return CheckError<SDL_GetError>(SDL_SetColorKey(m_surface.get(), flags, color), "Could not set key color");
}
