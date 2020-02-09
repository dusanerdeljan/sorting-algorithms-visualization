/*
Sorting algorithms visualization made using olcPixelGameEngine
Copyright (C) 2020 Dušan Erdeljan

This file is part of sorting-algorithms-visualization

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

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
