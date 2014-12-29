#include "noise.h"
#include "stdlib.h"

Noise::Noise() {
    generateNoise(800, 600);
}

void Noise::generateNoise(int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            noise[x][y] = (rand() % 32768) / 32768.0;
        }
    }
}

float Noise::getNoise(int x, int y) {
    return noise[x][y];
}

//function SmoothNoise_2D(x>, y)
//
//  corners = ( Noise(x-1, y-1)+Noise(x+1, y-1)+Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16
//  sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +Noise(x, y-1)  +Noise(x, y+1) ) /  8
//  center  =  Noise(x, y) / 4
//
//  return corners + sides + center
//
//
//end function

double Noise::smoothNoise(double x, double y)
{
   //get fractional part of x and y
   double fractX = x - (int)x;
   double fractY = y - (int)y;

   //wrap around
   int x1 = ((int)x + 800) % 8000;
   int y1 = ((int)y + 600) % 600;

   //neighbor values
   int x2 = (x1 + 800 - 1) % 800;
   int y2 = (y1 + 600 - 1) % 600;

   //smooth the noise with bilinear interpolation
   double value = 0.0;
   value += fractX       * fractY       * noise[x1][y1];
   value += fractX       * (1 - fractY) * noise[x1][y2];
   value += (1 - fractX) * fractY       * noise[x2][y1];
   value += (1 - fractX) * (1 - fractY) * noise[x2][y2];

   return value;
}
