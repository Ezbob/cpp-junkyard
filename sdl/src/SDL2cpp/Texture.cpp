#include "SDL.h"
#include "SDL2cpp/Texture.hpp"
#include <memory>

SDLTexture::SDLTexture(SDLRenderer &renderer) : m_texture(nullptr), m_renderer((SDL_Renderer *) renderer), m_width(0), m_height(0) {}
SDLTexture::SDLTexture(SDL_Renderer *renderer) : m_texture(nullptr), m_renderer(renderer), m_width(0), m_height(0) {}

void SDLTexture::load(SDL_Texture *texture, int width, int height) {
    m_texture = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
    m_height = height;
    m_width = width;
    if (m_texture == nullptr) {
        std::cerr << "Error: Could not load texture: " << SDL_GetError() << std::endl;
    }
}

void SDLTexture::load(SDL_Surface *surface) {
    SDL_Texture *newtexture = SDL_CreateTextureFromSurface(m_renderer, surface);
    m_texture = std::shared_ptr<SDL_Texture>(newtexture, SDL_DestroyTexture);
    m_height = surface->h;
    m_width = surface->w;
    if (m_texture == nullptr) {
        std::cerr << "Error: Could not load texture: " << SDL_GetError() << std::endl;
    }
}


void SDLTexture::load(SDLSurface &surface) {
    SDL_Texture *newtexture = SDL_CreateTextureFromSurface(m_renderer, (SDL_Surface *) surface);
    m_texture = std::shared_ptr<SDL_Texture>(newtexture, SDL_DestroyTexture);
    m_height = surface.getHeight();
    m_width = surface.getWidth();
    if (m_texture == nullptr) {
        std::cerr << "Error: Could not load texture: " << SDL_GetError() << std::endl;
    }
}

bool SDLTexture::isLoaded() {
    return (m_texture != nullptr);
}

void SDLTexture::render(int x, int y) {
    SDL_Rect quad = {x, y, m_width, m_height};
    CheckSDLError(SDL_RenderCopy(m_renderer, m_texture.get(), nullptr, &quad), "Cloud not render texture");
}

void SDLTexture::render(int x, int y, SDL_Rect &clip) {
    SDL_Rect quad = {x, y, clip.w, clip.h};
    CheckSDLError(SDL_RenderCopy(m_renderer, m_texture.get(), &clip, &quad), "Cloud not render clip texture");
}

void SDLTexture::render(int x, int y, SDL_Rect &clip, SDL_RendererFlip &flip) {
    SDL_Rect quad = {x, y, clip.w, clip.h};
    CheckSDLError(SDL_RenderCopyEx(m_renderer, m_texture.get(), &clip, &quad, 0, nullptr, flip), "Cloud not render clip texture");
}

void SDLTexture::render(int x, int y, SDL_RendererFlip &flip) {
    SDL_Rect quad = {x, y, m_width, m_height};
    CheckSDLError(SDL_RenderCopyEx(m_renderer, m_texture.get(), nullptr, &quad, 0, nullptr, flip), "Cloud not render clip texture");
}