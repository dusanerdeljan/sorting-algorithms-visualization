#include "MergeSort.h"

void MergeSort::Merge(std::vector<int>& numbers, int left, int mid, int right, std::vector<Animation>& animations) const
{
	if (numbers[mid] < numbers[left])
		return;
	int start = mid + 1;
	while (left <= mid && start <= right)
	{
		animations.push_back(Animation(AnimationType::COMPARE, left, start));
		if (numbers[left] < numbers[start])
		{
			left++;
		}
		else
		{
			int f = numbers[start];
			int index = start;

			while (index != left)
			{
				animations.push_back(Animation(AnimationType::SWAP, index, index-1));
				numbers[index] = numbers[index - 1];
				index--;
			}
			numbers[left] = f;
			left++;
			mid++;
			start++;
		}
	}
}

void MergeSort::MergeSortHelper(std::vector<int>& numbers, int left, int right, std::vector<Animation>& animations) const
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		MergeSortHelper(numbers, left, mid, animations);
		MergeSortHelper(numbers, mid + 1, right, animations);
		Merge(numbers, left, mid, right, animations);
	}
}

std::vector<Animation> MergeSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	MergeSortHelper(numbers, 0, numbers.size() - 1, animations);
	return animations;
}
