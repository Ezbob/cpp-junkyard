#include "SDL2cpp/Renderer.hpp"
#include "SDL2cpp/Texture.hpp"
#include "SDL2cpp/ErrorCheck.hpp"
#include "SDL.h"
#include <memory>

SDLRenderer::SDLRenderer(SDL_Window *window, int index, uint32_t rendererFlags) {
    m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window, index, rendererFlags), SDL_DestroyRenderer);
    m_window_parent = window;

    CheckSDLNullError(m_renderer.get(), "Could not initialize renderer");
}

SDLRenderer::SDLRenderer() {}

void SDLRenderer::load(SDL_Window *window, int index, uint32_t rendererFlags) {
    m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window, index, rendererFlags), SDL_DestroyRenderer);
    m_window_parent = window;
    if (m_renderer == nullptr) {
        std::cerr << "Error: Could not initialize renderer: " << SDL_GetError() << std::endl;
    }
}

void SDLRenderer::load(SDLWindow &window, int index, uint32_t rendererFlags) {
    m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer((SDL_Window *) window, index, rendererFlags), SDL_DestroyRenderer);
    m_window_parent = (SDL_Window *) window;
    if (m_renderer == nullptr) {
        std::cerr << "Error: Could not initialize renderer: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture *SDLRenderer::createTextureFromSurface(SDL_Surface &surface) {
    return SDL_CreateTextureFromSurface(m_renderer.get(), &surface);
}

SDL_Texture *SDLRenderer::createTextureFromSurface(SDL_Surface *surface) {
    return SDL_CreateTextureFromSurface(m_renderer.get(), surface);
}

bool SDLRenderer::clear() {
    return CheckSDLError(SDL_RenderClear(m_renderer.get()), "Could not clear renderer");
}

bool SDLRenderer::copyTexture(SDLTexture &texture, SDL_Rect *src, SDL_Rect *dest) {
    return CheckSDLError(SDL_RenderCopy(m_renderer.get(), (SDL_Texture *) texture, src, dest), "Could not copy texture to renderer");
}

void SDLRenderer::updateScreen() const {
    SDL_RenderPresent(m_renderer.get());
}

bool SDLRenderer::setColor(int r, int g, int b, int a) {
    return CheckSDLError(SDL_SetRenderDrawColor(m_renderer.get(), r, g, b, a), "Could not set renderer color");
}

bool SDLRenderer::drawRect(const SDL_Rect *fillRect) {
    return CheckSDLError(SDL_RenderDrawRect(m_renderer.get(), fillRect), "Could not draw rectangle");
}

bool SDLRenderer::drawRect(const SDL_Rect &fillRect) {
    return CheckSDLError(SDL_RenderDrawRect(m_renderer.get(), &fillRect), "Could not draw rectangle");
}

bool SDLRenderer::fillRect(const SDL_Rect *fillRect) {
    return CheckSDLError(SDL_RenderFillRect(m_renderer.get(), fillRect), "Could not fill rectangle");
}

bool SDLRenderer::fillRect(const SDL_Rect &fillRect) {
    return CheckSDLError(SDL_RenderFillRect(m_renderer.get(), &fillRect), "Could not fill rectangle");
}

bool SDLRenderer::drawLine(int x1, int y1, int x2, int y2) {
    return CheckSDLError(SDL_RenderDrawLine(m_renderer.get(), x1, y1, x2, y2), "Could not draw line");
}

bool SDLRenderer::drawPoint(int x, int y) {
    return CheckSDLError(SDL_RenderDrawPoint(m_renderer.get(), x, y), "Could not draw point"); 
}

bool SDLRenderer::setViewPort(SDL_Rect &rect) {
    return CheckSDLError(SDL_RenderSetViewport(m_renderer.get(), &rect), "Could not set view port");
}

bool SDLRenderer::isLoaded() { 
    return m_renderer != nullptr;
}

SDLTexture SDLRenderer::makeTexture() {
    return SDLTexture(m_renderer.get());
}
