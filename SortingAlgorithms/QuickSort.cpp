#include "QuickSort.h"

int QuickSort::Partition(std::vector<int>& numbers, int low, int high, std::vector<Animation>& animations) const
{
	int pivot = numbers[high];  
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		animations.push_back(Animation(AnimationType::COMPARE, j, high));
		if (numbers[j] < pivot)
		{
			i++;  
			std::swap(numbers[i], numbers[j]);
			animations.push_back(Animation(AnimationType::SWAP, i, j));
		}
	}
	std::swap(numbers[i + 1], numbers[high]);
	animations.push_back(Animation(AnimationType::SWAP, i + 1, high));
	return (i + 1);
}

void QuickSort::QuickSortHelper(std::vector<int>& numbers, int low, int high, std::vector<Animation>& animations) const
{
	if (low < high)
	{
		int pivot = Partition(numbers, low, high, animations);
		QuickSortHelper(numbers, low, pivot - 1, animations);
		QuickSortHelper(numbers, pivot + 1, high, animations);
	}
}

std::vector<Animation> QuickSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	QuickSortHelper(numbers, 0, numbers.size() - 1, animations);
	return animations;
}
