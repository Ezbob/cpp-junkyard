#include "SDL.hpp"

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
