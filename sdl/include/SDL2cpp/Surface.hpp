#ifndef HEADER_GUARD_ae78126d2bc5ee4610e84cb0f11eac44
#define HEADER_GUARD_ae78126d2bc5ee4610e84cb0f11eac44

#include "SDL.h"
#include "SDL_ttf.h"
#include <memory>

class SDLSurface {

public:
    SDLSurface(SDL_Surface *surface);
    SDLSurface();

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

#endif
