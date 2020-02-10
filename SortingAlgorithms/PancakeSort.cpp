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

#include "PancakeSort.h"

void PancakeSort::Reverse(std::vector<int>& numbers, int n, std::vector<Animation>& animations) const
{
	int startIndex = 0;
	while (startIndex < n)
	{
		animations.push_back(Animation(AnimationType::SWAP, startIndex, n));
		std::swap(numbers[startIndex++], numbers[n--]);
	}
}

int PancakeSort::FindMaxIndex(std::vector<int>& numbers, int n, std::vector<Animation>& animations) const
{
	int maxIndex = 0;
	for (int i = 1; i < n; i++)
	{
		animations.push_back(Animation(AnimationType::COMPARE, i, maxIndex));
		if (numbers[i] > numbers[maxIndex])
			maxIndex = i;
	}
	return maxIndex;
}

std::vector<Animation> PancakeSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	for (int n = numbers.size(); n > 1; n--)
	{
		int maxIndex = FindMaxIndex(numbers, n, animations);
		if (maxIndex != n - 1)
		{
			Reverse(numbers, maxIndex, animations);
			Reverse(numbers, n - 1, animations);
		}
	}
	return animations;
}
