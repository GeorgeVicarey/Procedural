/*
 * perlin.h
 *
 *  Created on: 15 Dec 2014
 *      Author: George
 */

#ifndef SRC_NOISE_H_
#define SRC_NOISE_H_

class Noise {
    public:
        float noiseTwoD (float x, float y);
        float interpolatedNoiseOne(float x, float y);
        float smoothNoise(float x, float Y);
        float interpolate(float a, float b, float x);
        float noiseOne(int x, int y);
};

#endif /* SRC_NOISE_H_ */
