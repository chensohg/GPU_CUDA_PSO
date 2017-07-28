#include "kernel.h"

float host_fitness_function(float x[])
{
	float y,yp;
	float res=0;
	float y1=1+(x[0]-1)/4;
	float yn=1+(x[NUM_OF_DIMENSIONS-1]-1)/4;

	res+=pow(sin(phi*y1),2)+pow(yn-1,2);

	for(int i=0;i<NUM_OF_DIMENSIONS-1;i++)
	{
		y=1+(x[i]-1)/4;
		yp=1+(x[i+1]-1)/4;
		res+=pow(y-1,2)*(1+10*pow(sin(phi*yp),2));
	}

	return res;
}

float getRandom(float low,float high)
{
	return low+float(((high-low)+1)*rand()/(RAND_MAX+1.0));
}

float getRandomClamped()
{
	return (float)rand()/(float)RAND_MAX;
}

void pso(float *positions,float *velocities,float *pBests,float *gBest)
{
	float tempParticle1[NUM_OF_DIMENSIONS];
	float tempParticle2[NUM_OF_DIMENSIONS];

	for(int iter=0;iter<MAX_ITER;iter++)
	{
		for(int i=0;i<NUM_OF_PARTICLES*NUM_OF_DIMENSIONS;i++)
		{
			float rp=getRandomClamped();
			float rg=getRandomClamped();

			velocities[i]=OMEGA*velocities[i]+c1*rp*(pBests[i]-positions[i])+c2*rg*(gBest[i%NUM_OF_DIMENSIONS]-positions[i]);

			positions[i]+=velocities[i];
		}

		for(int i=0;i<NUM_OF_PARTICLES*NUM_OF_DIMENSIONS;i+=NUM_OF_DIMENSIONS)
		{
			for(int j=0;j<NUM_OF_DIMENSIONS;j++)
			{
				tempParticle1[j]=positions[i+j];
				tempParticle2[j]=pBests[i+j];
			}

			if(host_fitness_function(tempParticle1)<host_fitness_function(tempParticle2))
			{
				for(int j=0;j<NUM_OF_DIMENSIONS;j++)
					pBests[i+j]=positions[i+j];

				if(host_fitness_function(tempParticle1)<host_fitness_function(gBest))
				{
					for(int j=0;j<NUM_OF_DIMENSIONS;j++)
						gBest[j]=pBests[i+j];
				}
			}
		}
	}
}
