#ifndef HEADER_GUARD_08570ec71d9036246ac3d05623b1f7bb
#define HEADER_GUARD_08570ec71d9036246ac3d05623b1f7bb

#include "ErrorCheck.hpp"
#include "SDL.h"
#include "Surface.hpp"

class SDLRenderer;

class SDLWindow {

public:
    SDLWindow(const char *title, int x, int y, int width, int height, uint32_t flags = SDL_WINDOW_SHOWN);
    SDLWindow(const char *title, int xy, int width, int height, uint32_t flags = SDL_WINDOW_SHOWN);
    SDLWindow();

    operator const SDL_Window *() const {
        return m_window;
    }

    explicit operator SDL_Window *() {
        return m_window;
    }

    void loadWindow(std::string windowName, int x, int y, int width, int height, uint32_t flags);
    void load(SDL_Window *wind);
    bool isLoaded();
    SDLSurface getSurface() const;
    bool updateScreen() const;

    SDLRenderer getRenderer(int index, uint32_t rendererFlags);

private:
    SDL_Window *m_window;
};

#endif
