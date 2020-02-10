#include "SlowSort.h"

void SlowSort::SlowSortHelper(std::vector<int>& numbers, size_t i, size_t j, std::vector<Animation>& animations) const
{
	if (i >= j) return;
	size_t mid = (i + j) / 2;
	SlowSortHelper(numbers, i, mid, animations);
	SlowSortHelper(numbers, mid + 1, j, animations);
	animations.push_back(Animation(AnimationType::COMPARE, j, mid));
	if (numbers[j] < numbers[mid])
	{
		animations.push_back(Animation(AnimationType::SWAP, j, mid));
		std::swap(numbers[j], numbers[mid]);
	}
	SlowSortHelper(numbers, i, j - 1, animations);
}

std::vector<Animation> SlowSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	SlowSortHelper(numbers, 0, numbers.size() - 1, animations);
	return animations;
}
