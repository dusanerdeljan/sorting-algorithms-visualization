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
