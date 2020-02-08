#pragma once
#include <vector>

enum class AnimationType {COMPARE, SWAP};

struct Animation
{
	AnimationType type;
	int firstIndex;
	int secondIndex;

	Animation(AnimationType type, int first, int second);
};

class Sort
{
public:
	virtual std::vector<Animation> SortNumbers(std::vector<int>& numbers) = 0;
};

