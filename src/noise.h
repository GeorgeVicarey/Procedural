/*
 * noise.h
 *
 *  Created on: 15 Dec 2014
 *      Author: George
 */

#ifndef SRC_NOISE_H_
#define SRC_NOISE_H_

class Noise {
    public:
        Noise();
        void generateNoise(int width, int height);
        float getNoise(int x, int y);
        double smoothNoise(double x, double y);
    private:
        double noise[800][600];
};

#endif /* SRC_NOISE_H_ */
