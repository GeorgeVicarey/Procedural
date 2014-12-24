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
};

#endif /* SRC_MAP_H_ */
