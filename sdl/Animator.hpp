#ifndef ANIMATOR_H_dbc46f9133f3f0f7103ecf9fae61de05
#define ANIMATOR_H_dbc46f9133f3f0f7103ecf9fae61de05

#include "SDL.hpp"
#include <array>

template<int columns, int rows>
class SpriteSheetAnimator {

    SDLTexture spriteSheetTexture;
    int frame;
    int sprite_width;
    int sprite_height;
    int framerate;
    int numberOfFrames = columns * rows;

    bool is_running = false;
    bool is_loaded = false;

    std::array<SDL_Rect, columns * rows> frames;

public:
    SpriteSheetAnimator(SDLTexture spriteSheet, int sprite_width, int sprite_height, int framerate = 16) : 
        spriteSheetTexture(std::move(spriteSheet)),
        frame(0), sprite_width(sprite_width),
        sprite_height(sprite_height),
        framerate(framerate) {

        int frame_index = 0;
        for (int j = 0; j < rows; ++j) {
            for (int i = 0; i < columns; ++i) {
                frames[frame_index].x = sprite_width * i;
                frames[frame_index].y = sprite_height * j;
                frames[frame_index].w = sprite_width;
                frames[frame_index].h = sprite_height;
                frame_index++;
            }
        }
        is_loaded = true;
    }

    SpriteSheetAnimator(SDLRenderer &renderer, int sprite_width, int sprite_height, int framerate = 16) : 
        spriteSheetTexture(renderer),
        frame(0), sprite_width(sprite_width),
        sprite_height(sprite_height),
        framerate(framerate) {
        for (int i = 0; i < numberOfFrames; ++i) {
            frames[i].x = sprite_width * i;
            frames[i].y = 0;
            frames[i].w = sprite_width;
            frames[i].h = sprite_height;
        }
    }

    void load(SDLTexture spriteSheet) {
        spriteSheetTexture = spriteSheet;
        is_loaded = true;
    }

    bool isLoaded() {
        return is_loaded;
    }

    void run() {
        is_running = true;
    }

    void stop() {
        is_running = false;
    }

    void render(int x, int y) {
        spriteSheetTexture.render(x, y, frames[(frame / framerate)]);
    }

    void tick() {
        if (is_running) {
            ++frame;

            if (frame / framerate >= numberOfFrames) {
                frame = 0;
            }
        }
    }

    int getSpriteHeight() const {
        return sprite_height;
    }

    int getSpriteWidth() const {
        return sprite_width;
    }

    bool isRunning() const {
        return is_running;
    }
};


#endif