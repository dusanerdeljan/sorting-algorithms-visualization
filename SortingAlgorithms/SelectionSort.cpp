#include "SelectionSort.h"

std::vector<Animation> SelectionSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	for (size_t i = 0; i < numbers.size()-1; i++)
	{
		size_t minIndex = i;
		for (size_t j = i+1; j < numbers.size(); j++)
		{
			if (numbers[j] < numbers[minIndex]) minIndex = j;
			animations.push_back(Animation(AnimationType::COMPARE, j, minIndex));
		}
		if (minIndex != i)
		{
			std::swap(numbers[i], numbers[minIndex]);
			animations.push_back(Animation(AnimationType::SWAP, i, minIndex));
		}
	}
	return animations;
}
