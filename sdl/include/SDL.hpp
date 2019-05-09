#ifndef SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3
#define SDL_HPP_HEADER_364be655e3b01471341a61c7489902c3

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <cstddef>
#include <memory>

enum class SDLExternLibs {
    SDL_IMAGE = 1,
    SDL_TTF
};

constexpr int CheckSDLError(int success, const char *message) {
    if (success != 0) { 
            std::cerr << "Error: " << message << ": " << SDL_GetError() << std::endl; 
    } 
    return success == 0;
}

class SDLSurface;
class SDLRenderer;
class SDLTexture;

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
                    is_initialized = false;
                } else {
                    is_initialized = is_initialized && true;
                }
                break;
            case SDLExternLibs::SDL_TTF:
                if ( TTF_Init() == -1 ) { // IMG_Init returns the flags set
                    std::cerr << "Error: Could not initialize SDL_TFF: " << TTF_GetError() << std::endl;
                    is_initialized = false;
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

private:
    SDL_Window *m_window;
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
    void loadSolidText(std::string text, TTF_Font &font, SDL_Color color = {0, 0, 0});

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
    SDLTexture(SDLRenderer &renderer) : m_texture(nullptr), m_renderer((SDL_Renderer *) renderer), m_width(0), m_height(0) {}
    SDLTexture(SDL_Renderer *renderer) : m_texture(nullptr), m_renderer(renderer), m_width(0), m_height(0) {}

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


// surface impl -------------------------------------------------------------------------------------


// Window impl -------------------------------------------------------------------------------------



// Renderer impl -------------------------------------------------------------------------------------

#endif