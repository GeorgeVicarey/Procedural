/**
 * Created:   25th December 2014
 *
 * Last edit: 25th December 2014
 *
 * Copyright George Vicarey
 */

#include "noise.h"
#include <tgmath.h>

//function Noise1(integer x, integer y)
//    n = x + y * 57
//    n = (n<<13) ^ n;
//    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 7fffffff) / 1073741824.0);
//  end function


float Noise::noiseOne(int x, int y) {
    int n = x + y * 57;
    n = (n<<13) ^ n;

    return (1.0 - ( (n* (n * n * 15731 + 789221) + 1376312589) & 7) / 1073741824.0);
}

//  function SmoothNoise_1(float x, float y)
//    corners = ( Noise(x-1, y-1)+Noise(x+1, y-1)+Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16
//    sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +Noise(x, y-1)  +Noise(x, y+1) ) /  8
//    center  =  Noise(x, y) / 4
//    return corners + sides + center
//  end function

float Noise::smoothNoise(float x, float y) {
    float corners = (noiseOne(x-1, y-1) + noiseOne(x+1, y-1) + noiseOne(x-1, y+1) + noiseOne(x+1, y+1) ) / 16;
    float sides = (noiseOne(x-1, y) + noiseOne(x+1, y) + noiseOne(x, y-1) + noiseOne(x, y+1) ) / 8;
    float center = noiseOne(x, y) / 4;

    return corners + sides + center;
}

//  function InterpolatedNoise_1(float x, float y)
//
//      integer_X    = int(x)
//      fractional_X = x - integer_X
//
//      integer_Y    = int(y)
//      fractional_Y = y - integer_Y
//
//      v1 = SmoothedNoise1(integer_X,     integer_Y)
//      v2 = SmoothedNoise1(integer_X + 1, integer_Y)
//      v3 = SmoothedNoise1(integer_X,     integer_Y + 1)
//      v4 = SmoothedNoise1(integer_X + 1, integer_Y + 1)
//
//      i1 = Interpolate(v1 , v2 , fractional_X)
//      i2 = Interpolate(v3 , v4 , fractional_X)
//
//      return Interpolate(i1 , i2 , fractional_Y)
//
//  end function

float Noise::interpolatedNoiseOne(float x, float y) {

    int intX = (int)x;
    float fractional_X = x - intX;

    int intY = (int)y;
    float fractional_Y = y - intY;

    float v1 = smoothNoise(intX, intY);
    float v2 = smoothNoise(intX + 1, intY);
    float v3 = smoothNoise(intX, intY + 1);
    float v4 = smoothNoise(intX +1, intY + 1);

    float i1 = interpolate(v1, v2, fractional_X);
    float i2 = interpolate(v3, v4, fractional_X);

    return interpolate(i1, i2, fractional_Y);
}

//function Cosine_Interpolate(a, b, x)
//  ft = x * 3.1415927
//  f = (1 - cos(ft)) * .5
//
//  return  a*(1-f) + b*f
//end of function

float Noise::interpolate(float a, float b, float x) {
    float ft = x * 3.145927;
    float f = (1 - cos(ft)) *  0.5;

    return a*(1-f) + b * f;
}

//  function PerlinNoise_2D(float x, float y)
//
//      total = 0
//      p = persistence
//      n = Number_Of_Octaves - 1
//
//      loop i from 0 to n
//
//          frequency = 2i
//          amplitude = pi
//
//          total = total + InterpolatedNoisei(x * frequency, y * frequency) * amplitude
//
//      end of i loop
//
//      return total
//
//  end function

float Noise::noiseTwoD(float x, float y) {
    float total = 0;

    float p = 0.5;      //persistence
    float n = 4 - 1;        //number of octaves - 1

    for (int i = 0; i <= n; i++) {
        float frequency = 2 * i;
        float amplitude = p * i;

        total = total + interpolatedNoiseOne(x * frequency, y * frequency) * amplitude;
    }

    return total;
}
