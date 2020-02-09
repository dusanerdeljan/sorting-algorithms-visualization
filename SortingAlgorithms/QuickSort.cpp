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
