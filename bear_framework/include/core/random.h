#pragma once

#include<random>

namespace bear { namespace core {

	static float randomZeroToOne()
	{
		float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return x;
	}

	static float randomInterval(float min, float max) {
		float x = randomZeroToOne();
		float range = max - min;
		return (range*x) + min;
	}

} }