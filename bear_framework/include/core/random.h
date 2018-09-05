#pragma once

#include<random>

namespace bear { namespace core {

	/*
	All of these interval functions assume max > min
	@ TODO: code a robust error checking for all max/min scenarios
	*/

	static int randomIntegerInterval(int min, int max) {
		int range = (max - min);
		int x = rand() % range;
		return (min + x);
	}

	static float randomFloatZeroToOne()
	{
		float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return x;
	}

	static float randomFloatInterval(float min, float max) {
		float x = randomFloatZeroToOne();
		float range = max - min;
		return (range*x) + min;
	}

} }