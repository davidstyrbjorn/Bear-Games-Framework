#pragma once

#include<random>

namespace bear { namespace core {

	static float randomZeroToOne()
	{
		float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		return x;
	}

} }