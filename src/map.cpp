/*
 * map.cpp
 *
 *  Created on: 23 Dec 2014
 *      Author: George
 */

#include "map.h"
#include "stdlib.h"
#include "noise.h"

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

int8_t pixels[800][600 * 3] = {};

Noise noise;

Map::Map() {
    populateArray();
}

Map::~Map() {

}

/**
 * Create an SDL surface from the array of pixel data
 */
SDL_Surface * Map::getSurface() {
    SDL_Surface * map = SDL_CreateRGBSurfaceFrom(&pixels, 800, 600, 8 * 3, 800 * 3, 0x0000FF,
            0x00FF00, 0xFF0000, 0);

    return map;
}

/**
 * NOT WORKING NEED TO FIX
 */
void Map::makeImage() {

}

void Map::populateArray() {
    for (int x = 0; x < 800; x++) {
        for (int y = 0; y < 600 * 3; y+=3) {
            pixels[x][y] = pixels[x][y + 1] = pixels[x][y + 2] = (256 * noise.smoothNoise((double)x/8.0, (double)y/8.0));
        }
    }
}
