#include "SDLExtra/Font.hpp"
#include "SDL2cpp/ErrorCheck.hpp"

TTFFont::~TTFFont() {
    if (m_font != nullptr) TTF_CloseFont(m_font);
}

void TTFFont::load(TTF_Font *font) {
    m_font = CheckNullError<TTF_Font, TTF_GetError>(font, "Could not initialze font");
    if ( m_font != nullptr ) m_isLoaded = true;
}

bool TTFFont::isLoaded() const {
    return m_font != nullptr;
}

void TTFFont::loadTTF(const std::string filepath, int ptsize) {
    m_font = CheckNullError<TTF_Font, TTF_GetError>(TTF_OpenFont(filepath.c_str(), ptsize), "Could not initialze font");
    if ( m_font != nullptr ) m_isLoaded = true;
}


