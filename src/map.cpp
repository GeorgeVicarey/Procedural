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

Noise noise;

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
//    std::ofstream out;
//    out.open("src/textures/map.ppm");
//
//    out << "P6" << std::endl << "800" << " " << "600" << std::endl << "255" << std::endl;
//
//    for (int h = 0; h < 600; h++) {
//        for (int w = 0; w < 800 * 3; w++) {
//            int8_t pixel = pixels[h * w];
//            out << pixel << " ";
//        }
//        out << std::endl;
//    }

}

void Map::populateArray() {
    for (int h = 0; h < 600;) {
        for (int w = 0; w < 800 * 3; w += 3) {
            int y = noise.noiseTwoD(h, w);
            int x = y;

            /*if (y < 10) {
                x = (255 / 10) * 1;
            } else if (y < 20) {
                x = (255 / 10) * 2;
            } else if (y < 30) {
                x = (255 / 10) * 3;
            } else if (y < 40) {
                x = (255 / 10) * 4;
            } else if (y < 50) {
                x = (255 / 10) * 5;
            } else if (y < 60) {
                x = (255 / 10) * 6;
            } else if (y < 70) {
                x = (255 / 10) * 7;
            } else if (y < 80) {
                x = (255 / 10) * 8;
            } else if (y < 90) {
                x = (255 / 10) * 9;
            } else if (y < 100) {
                x = (255 / 10) * 10;
            }*/

            int r = x;
            int g = x;
            int b = x;

            pixels[h][w] = r;
            pixels[h][w + 1] = g;
            pixels[h][w + 2] = b;
        }
    }
}
