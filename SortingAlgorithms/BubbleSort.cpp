#include "BubbleSort.h"

std::vector<Animation> BubbleSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	for (size_t i = 0; i < numbers.size()-1; i++)
	{
		for (size_t j = 0; j < numbers.size() - i - 1; j++)
		{
			animations.push_back(Animation(AnimationType::COMPARE, j, j + 1));
			if (numbers[j] > numbers[j + 1])
			{
				std::swap(numbers[j], numbers[j + 1]);
				animations.push_back(Animation(AnimationType::SWAP, j, j + 1));
			}
		}
	}
	return animations;
}
