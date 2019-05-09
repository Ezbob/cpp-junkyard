#ifndef HEADER_GUARD_e73311f1c7af9dc9fb705468721e084a
#define HEADER_GUARD_e73311f1c7af9dc9fb705468721e084a

#include "Renderer.hpp"
#include "Surface.hpp"
#include "SDL.h"

class SDLRenderer;

class SDLTexture {

public:
    SDLTexture(SDLRenderer &renderer);
    SDLTexture(SDL_Renderer *renderer);

    void load(SDL_Texture *texture, int w, int h);
    void load(SDL_Surface *surface);
    void load(SDLSurface &surface);

    bool isLoaded();

    operator const SDL_Texture *() const {
        return m_texture.get();
    }

    explicit operator SDL_Texture *() const {
        return m_texture.get();
    }

    int getHeight() const {
        return m_height;
    }

    int getWidth() const {
        return m_width;
    }

    void render(int x = 0, int y = 0);
    void render(int x, int y, SDL_Rect &clip);
    void render(int x, int y, SDL_Rect &clip, SDL_RendererFlip &flip);
    void render(int x, int y, SDL_RendererFlip &flip);

private:
    std::shared_ptr<SDL_Texture> m_texture;
    SDL_Renderer *m_renderer;
    int m_width;
    int m_height;
};

#endif
