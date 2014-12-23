/*
 * game.h
 *
 *  Created on: 10 Nov 2014
 *      Author: gv30
 */

#ifndef GAME_H_
#define GAME_H_

#define GLEW_STATIC
#include "global.h"

        const int gridWidth = 4;
        const int gridHeight = 10;

class Game {
    public:
        Game();
        ~Game();
        bool init();
        bool objectInit();
        bool createWindow(const char*, int, int);
        bool handleEvents(SDL_Event);
        bool update();
        bool render();
        void swapBuffers();

    private:
        SDL_Window* window;
        SDL_Surface* screenSurface;
        SDL_Surface* mapSurface;
};

#endif /* GAME_H_ */
