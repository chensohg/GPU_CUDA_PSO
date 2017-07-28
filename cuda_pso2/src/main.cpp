#include "kernel.h"

int main(void)
{
	float positions[NUM_OF_PARTICLES*NUM_OF_DIMENSIONS];
	float velocities[NUM_OF_PARTICLES*NUM_OF_DIMENSIONS];
	float pBests[NUM_OF_PARTICLES*NUM_OF_DIMENSIONS];

	float gBest[NUM_OF_DIMENSIONS];

	srand((unsigned)time(NULL));

	//"=================BEGIN OF GPU=====================\n"
	for(int i=0;i<NUM_OF_PARTICLES*NUM_OF_DIMENSIONS;i++)
	{
		positions[i]=getRandom(START_RANGE_MIN,START_RANGE_MAX);
		pBests[i]=positions[i];
		velocities[i]=0;
	}

	for(int i=0;i<NUM_OF_DIMENSIONS;i++)
		gBest[i]=pBests[i];

	clock_t begin=clock();

	cuda_pso(positions,velocities,pBests,gBest);

	clock_t end=clock();

	printf("=================GPU=====================\n");

	printf("Time elapsed:%10.3lf s\n",(double)(end-begin)/CLOCKS_PER_SEC);

	for(int i=0;i<NUM_OF_DIMENSIONS;i++)
		printf("x%d=%f\n",i,gBest[i]);

	printf("Minimum=%f\n",host_fitness_function(gBest));

	//"=================END OF GPU=====================\n"

	//"=================BEGIN OF CPU=====================\n"

	for(int i=0;i<NUM_OF_PARTICLES*NUM_OF_DIMENSIONS;i++)
	{
		positions[i]=getRandom(START_RANGE_MIN,START_RANGE_MAX);
		pBests[i]=positions[i];
		velocities[i]=0;
	}

	for(int i=0;i<NUM_OF_DIMENSIONS;i++)
		gBest[i]=pBests[i];

	clock_t cpu_begin=clock();

	pso(positions,velocities,pBests,gBest);

	clock_t cpu_end=clock();

	printf("=================CPU=====================\n");

	printf("Time elapsed:%10.3lf s\n",(double)(cpu_end-cpu_begin)/CLOCKS_PER_SEC);

	for(int i=0;i<NUM_OF_DIMENSIONS;i++)
		printf("x%d=%f\n",i,gBest[i]);

	printf("Minimum=%f\n",host_fitness_function(gBest));

	//"=================END OF CPU=====================\n"

	return 0;
}


