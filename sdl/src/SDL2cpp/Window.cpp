#include "SDL2cpp/ErrorCheck.hpp"
#include "SDL2cpp/Window.hpp"
#include "SDL2cpp/Renderer.hpp"
#include "SDL.h"

SDLWindow::SDLWindow(const char *title, int x, int y, int width, int height, uint32_t flags) {
    m_window = CheckSDLNullError(SDL_CreateWindow(
        title, x, y, width, height, flags
    ), "Window could not be initialized");
}

SDLWindow::SDLWindow(const char *title, int xy, int width, int height, uint32_t flags) {
    m_window = CheckSDLNullError(SDL_CreateWindow(
        title, xy, xy, width, height, flags
    ), "Window could not be initialized");
}

SDLWindow::SDLWindow() {}

void SDLWindow::load(SDL_Window *wind) {
    m_window = wind;
    if (m_window == nullptr) {
        std::cerr << "Error: Window could not be initialize: " << SDL_GetError() << std::endl;
    }
}

SDLSurface SDLWindow::getSurface() const {
    return SDLSurface(SDL_GetWindowSurface(m_window));
}

bool SDLWindow::updateScreen() const {
    return SDL_UpdateWindowSurface(m_window) == 0;
}

bool SDLWindow::isLoaded() {
    return m_window != nullptr;
}

void SDLWindow::loadWindow(std::string windowName, int x, int y, int width, int height, uint32_t flags) {
    m_window = SDL_CreateWindow(windowName.c_str(), x, y, width, height, flags);

    if (m_window == nullptr) {
        std::cerr << "Error: Window could not be initialize: " << SDL_GetError() << std::endl;
    }
}

SDLRenderer SDLWindow::getRenderer(int index, uint32_t rendererFlags) {
    return SDLRenderer(m_window, index, rendererFlags);
}
