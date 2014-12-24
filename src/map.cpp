/*
 * map.cpp
 *
 *  Created on: 23 Dec 2014
 *      Author: George
 */

#include "map.h"
#include "stdlib.h"

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

int8_t pixels[800 * 600 * 3] = {};

Map::Map() {
    populateArray();
}

Map::~Map() {

}

SDL_Surface * Map::getSurface() {
    SDL_Surface * map = SDL_CreateRGBSurfaceFrom(&pixels, 800, 600, 8 * 3, 800 * 3, 0x0000FF,
            0x00FF00, 0xFF0000, 0);

    return map;
}

/**
 * NOT OWRKING NEED TO FIX
 */
void Map::makeImage() {
    std::ofstream out;
    out.open("src/textures/map.ppm");

    out << "P6" << std::endl << "800" << " " << "600" << std::endl << "255" << std::endl;

    for (int h = 0; h < 600; h++) {
        for (int w = 0; w < 800 * 3; w++) {
            int8_t pixel = pixels[h * w];
            out << pixel << " ";
        }
        out << std::endl;
    }

}

void Map::populateArray() {
    for (int i = 0; i < 800 * 600 * 3; i += 3) {
        int y = rand() % 255;
        int r = y;
        int g = y;
        int b = y;

        pixels[i] = r;
        pixels[i + 1] = g;
        pixels[i + 2] = b;
    }
}
