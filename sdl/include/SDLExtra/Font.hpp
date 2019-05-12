#ifndef HEADER_GUARD_9d0f70840337db3e8dfc9f59e0796fbd
#define HEADER_GUARD_9d0f70840337db3e8dfc9f59e0796fbd

#include "SDL_ttf.h"
#include <string>

class TTFFont {

    TTF_Font *m_font;

    bool m_isLoaded = false;

public:
    TTFFont() = default;
    ~TTFFont();

    operator const TTF_Font *() const {
        return m_font;
    }

    explicit operator TTF_Font *() const {
        return m_font;
    }

    void loadTTF(const std::string filepath, int ptsize);

    void load(TTF_Font *font);
    bool isLoaded() const;

};

#endif
