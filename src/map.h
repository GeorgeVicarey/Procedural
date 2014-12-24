/*
 * map.h
 *
 *  Created on: 23 Dec 2014
 *      Author: George
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "global.h"

class Map {
    public:
        Map();
        ~Map();
        void populateArray();
        void makeImage();
        SDL_Surface* getSurface();

        // returns pixel array (the map data)
        int8_t* getMap() {return pixels;};
    private:
        int8_t pixels[800 * 600 * 3] = {};
};

#endif /* SRC_MAP_H_ */
