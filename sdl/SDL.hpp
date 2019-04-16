#ifndef SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3
#define SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <cstddef>
#include <memory>

enum class SDLExternLibs {
    SDL_IMAGE = 1,
};

constexpr int CheckSDLError(int success, const char *message) {
    if (success != 0) { 
            std::cerr << "Error: " << message << ": " << SDL_GetError() << std::endl; 
    } 
    return success == 0;
}

class SDLSurface;
class SDLRenderer;

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

    bool loadExternLib(SDLExternLibs libsChosen, uint32_t libFlags = 0) {

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
            m_libs_set |= static_cast<int>(libsChosen);

        return is_initialized;
    }

    ~SDLGlobals() {
        SDL_Quit();
        uint32_t imageFeature = static_cast<uint32_t>(SDLExternLibs::SDL_IMAGE);
        if ( (m_libs_set & imageFeature) == imageFeature ) {
            IMG_Quit();
        }
    }

    uint32_t m_libs_set = 0;
    uint32_t m_flags_set = 0;
    bool is_initialized = false;
    bool is_playing = true;
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

    operator const SDL_Window *const() const {
        return m_window;
    }

    explicit operator SDL_Window *() const {
        return m_window;
    }

    void loadWindow(std::string windowName, int x, int y, int width, int height, uint32_t flags);
    void load(SDL_Window *wind);
    bool isLoaded();
    SDLSurface getSurface() const;
    bool updateScreen() const;

private:
    SDL_Window *m_window;
};

class SDLSurface {

public:
    SDLSurface(SDL_Surface *surface) {
        m_surface = std::shared_ptr<SDL_Surface>(surface, SDL_FreeSurface);
        m_width = surface->w;
        m_height = surface->h;
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

    int setKeyColor(int flags, uint32_t color);

    int getHeight() const {
        return m_height;
    }

    int getWidth() const {
        return m_width;
    }

    /**
     * Convert the internal surface pixel format to the other surface's pixelformat
     */
    void convertToFormat(const SDLSurface &other);

    const SDL_PixelFormat *pixelFormat() const;
    void fill(int r, int g, int b);
    uint32_t rgbColor(int r, int g, int b) const;

private:
    std::shared_ptr<SDL_Surface> m_surface;
    int m_width;
    int m_height;
};

class SDLTexture {

public:
    SDLTexture() : m_texture(nullptr), m_renderer(nullptr), m_width(0), m_height(0) {}

    void load(SDL_Texture *texture, int w, int h, SDLRenderer &parent);
    void load(SDL_Surface *surface, SDLRenderer &parent);
    void load(SDLSurface &surface, SDLRenderer &parent);

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

    void render(int x = 0, int y = 0) {
        SDL_Rect quad = {x, y, m_width, m_height};
        CheckSDLError(SDL_RenderCopy(m_renderer, m_texture.get(), nullptr, &quad), "Cloud not render texture");
    }

    void render(int x, int y, SDL_Rect &clip) {
        SDL_Rect quad = {x, y, clip.w, clip.h};
        CheckSDLError(SDL_RenderCopy(m_renderer, m_texture.get(), &clip, &quad), "Cloud not render clip texture");
    }

private:
    std::shared_ptr<SDL_Texture> m_texture;
    SDL_Renderer *m_renderer;
    int m_width;
    int m_height;
};

class SDLRenderer {

public:
    SDLRenderer(SDL_Window *window, int index, uint32_t rendererFlags) {
        m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window, index, rendererFlags), SDL_DestroyRenderer);
        m_window_parent = window;
        if (m_renderer == nullptr) {
            std::cerr << "Error: Could not initialize renderer: " << SDL_GetError() << std::endl;
        }
    }

    SDLRenderer() {}

    void load(SDL_Window *window, int index, uint32_t rendererFlags) {
        m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(window, index, rendererFlags), SDL_DestroyRenderer);
        m_window_parent = window;
        if (m_renderer == nullptr) {
            std::cerr << "Error: Could not initialize renderer: " << SDL_GetError() << std::endl;
        }
    }

    void load(SDLWindow &window, int index, uint32_t rendererFlags) {
        m_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer((SDL_Window *) window, index, rendererFlags), SDL_DestroyRenderer);
        m_window_parent = (SDL_Window *) window;
        if (m_renderer == nullptr) {
            std::cerr << "Error: Could not initialize renderer: " << SDL_GetError() << std::endl;
        }
    }

    SDL_Texture *createTextureFromSurface(SDL_Surface &surface) {
        return SDL_CreateTextureFromSurface(m_renderer.get(), &surface);
    }

    SDL_Texture *createTextureFromSurface(SDL_Surface *surface) {
        return SDL_CreateTextureFromSurface(m_renderer.get(), surface);
    }

    bool clear() {
        return CheckSDLError(SDL_RenderClear(m_renderer.get()), "Could not clear renderer");
    }

    bool copyTexture(SDLTexture &texture, SDL_Rect *src = nullptr, SDL_Rect *dest = nullptr) {
        return CheckSDLError(SDL_RenderCopy(m_renderer.get(), (SDL_Texture *) texture, src, dest), "Could not copy texture to renderer");
    }

    void updateScreen() const {
        SDL_RenderPresent(m_renderer.get());
    }

    bool setColor(int r, int g, int b, int a = 0xFF) {
        return CheckSDLError(SDL_SetRenderDrawColor(m_renderer.get(), r, g, b, a), "Could not set renderer color");
    }

    bool drawRect(const SDL_Rect *fillRect) {
        return CheckSDLError(SDL_RenderDrawRect(m_renderer.get(), fillRect), "Could not draw rectangle");
    }

    bool drawRect(const SDL_Rect &fillRect) {
        return CheckSDLError(SDL_RenderDrawRect(m_renderer.get(), &fillRect), "Could not draw rectangle");
    }

    bool fillRect(const SDL_Rect *fillRect) {
        return CheckSDLError(SDL_RenderFillRect(m_renderer.get(), fillRect), "Could not fill rectangle");
    }

    bool fillRect(const SDL_Rect &fillRect) {
        return CheckSDLError(SDL_RenderFillRect(m_renderer.get(), &fillRect), "Could not fill rectangle");
    }

    bool drawLine(int x1, int y1, int x2, int y2) {
        return CheckSDLError(SDL_RenderDrawLine(m_renderer.get(), x1, y1, x2, y2), "Could not draw line");
    }

    bool drawPoint(int x, int y) {
        return CheckSDLError(SDL_RenderDrawPoint(m_renderer.get(), x, y), "Could not draw point"); 
    }

    bool setViewPort(SDL_Rect &rect) {
        return CheckSDLError(SDL_RenderSetViewport(m_renderer.get(), &rect), "Could not set view port");
    }

    bool isLoaded() { 
        return m_renderer != nullptr;
    }

    operator const SDL_Renderer *const() const {
        return m_renderer.get();
    }

    explicit operator SDL_Renderer *() const {
        return m_renderer.get();
    }

private:
    SDL_Window *m_window_parent = nullptr;
    std::shared_ptr<SDL_Renderer> m_renderer = nullptr;
};


// texture impl -------------------------------------------------------------------------------------

void SDLTexture::load(SDL_Texture *texture, int width, int height, SDLRenderer &renderer) {
    m_texture = std::shared_ptr<SDL_Texture>(texture, SDL_DestroyTexture);
    m_height = height;
    m_width = width;
    m_renderer = (SDL_Renderer *) renderer;
    if (m_texture == nullptr) {
        std::cerr << "Error: Could not load texture: " << SDL_GetError() << std::endl;
    }
}

void SDLTexture::load(SDL_Surface *surface, SDLRenderer &renderer) {
    SDL_Texture *newtexture = SDL_CreateTextureFromSurface((SDL_Renderer *) renderer, surface);
    m_texture = std::shared_ptr<SDL_Texture>(newtexture, SDL_DestroyTexture);
    m_renderer = (SDL_Renderer *) renderer;
    m_height = surface->h;
    m_width = surface->w;
    if (m_texture == nullptr) {
        std::cerr << "Error: Could not load texture: " << SDL_GetError() << std::endl;
    }
}

void SDLTexture::load(SDLSurface &surface, SDLRenderer &renderer) {
    SDL_Texture *newtexture = SDL_CreateTextureFromSurface((SDL_Renderer *) renderer, (SDL_Surface *) surface);
    m_texture = std::shared_ptr<SDL_Texture>(newtexture, SDL_DestroyTexture);
    m_renderer = (SDL_Renderer *) renderer;
    m_height = surface.getHeight();
    m_width = surface.getWidth();
    if (m_texture == nullptr) {
        std::cerr << "Error: Could not load texture: " << SDL_GetError() << std::endl;
    }
}

bool SDLTexture::isLoaded() {
    return (m_texture != nullptr);
}


// surface impl -------------------------------------------------------------------------------------

void SDLSurface::load(SDL_Surface *suf) {
    m_surface = std::shared_ptr<SDL_Surface>(suf, SDL_FreeSurface);
    m_height = suf->h;
    m_width = suf->w;
    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
    }
}

void SDLSurface::loadBMP(std::string filename) {
    m_surface = std::shared_ptr<SDL_Surface>(SDL_LoadBMP(filename.c_str()), SDL_FreeSurface);
    m_height = m_surface->h;
    m_width = m_surface->w;
    if (m_surface == nullptr) {
        std::cerr << "Error: Surface could not be initialize: " << SDL_GetError() << std::endl;
    }
}

void SDLSurface::loadPNG(std::string filename) {
    m_surface = std::shared_ptr<SDL_Surface>(IMG_Load(filename.c_str()), SDL_FreeSurface);
    m_height = m_surface->h;
    m_width = m_surface->w;
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

int SDLSurface::setKeyColor(int flags, uint32_t color) {
    return CheckSDLError(SDL_SetColorKey(m_surface.get(), flags, color), "Could not set key color");
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

#endif