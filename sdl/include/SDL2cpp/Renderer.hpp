#ifndef HEADER_GUARD_a04ab214bef1adcd47b92de3a2c703e2
#define HEADER_GUARD_a04ab214bef1adcd47b92de3a2c703e2

#include "SDL.hpp"

class SDLTexture;
class SDLWindow;

class SDLRenderer {

public:
    SDLRenderer(SDL_Window *window, int index, uint32_t rendererFlags);
    SDLRenderer();

    void load(SDL_Window *window, int index, uint32_t rendererFlags);
    void load(SDLWindow &window, int index, uint32_t rendererFlags);
    SDL_Texture *createTextureFromSurface(SDL_Surface &surface);
    SDL_Texture *createTextureFromSurface(SDL_Surface *surface);

    bool clear();
    bool copyTexture(SDLTexture &texture, SDL_Rect *src = nullptr, SDL_Rect *dest = nullptr);
    void updateScreen() const;
    bool setColor(int r, int g, int b, int a = 0xFF);
    bool drawRect(const SDL_Rect *fillRect);
    bool drawRect(const SDL_Rect &fillRect);
    bool fillRect(const SDL_Rect *fillRect);
    bool fillRect(const SDL_Rect &fillRect);
    bool drawLine(int x1, int y1, int x2, int y2);
    bool drawPoint(int x, int y);
    bool setViewPort(SDL_Rect &rect);

    bool isLoaded();

    /**
     * Factory method for creating new textures
     */
    SDLTexture makeTexture();

    operator const SDL_Renderer *() const {
        return m_renderer.get();
    }

    explicit operator SDL_Renderer *() const {
        return m_renderer.get();
    }

private:
    SDL_Window *m_window_parent = nullptr;
    std::shared_ptr<SDL_Renderer> m_renderer = nullptr;
};

#endif
