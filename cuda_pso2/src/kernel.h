/*
 * kernel.h
 *
 *  Created on: Jul 27, 2017
 *      Author: root
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int NUM_OF_PARTICLES=512;
const int NUM_OF_DIMENSIONS=3;
const int MAX_ITER=30000;
const float START_RANGE_MIN=-5.12f;
const float START_RANGE_MAX=5.12f;
const float OMEGA=0.5;
const float c1=1.5;
const float c2=1.5;
const float phi=3.1415;

float getRandom(float low,float high);
float getRandomClamped();
float host_fitness_function(float x[]);

void pso(float *positions,float *velocities,float *pBests,float *gBest);

extern "C" void cuda_pso(float *positions,float *velocities,float *pBests,float *gBest);

#endif /* KERNEL_H_ */
