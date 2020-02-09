#include "InsertionSort.h"

std::vector<Animation> InsertionSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	for (size_t i = 1; i < numbers.size(); i++)
	{
		int j = i;
		while (j > 0 && (numbers[j] < numbers[j-1]))
		{
			animations.push_back(Animation(AnimationType::COMPARE, j, j - 1));
			std::swap(numbers[j], numbers[j - 1]);
			animations.push_back(Animation(AnimationType::SWAP, j, j - 1));
			j -= 1;
		}
	}
	return animations;
}
