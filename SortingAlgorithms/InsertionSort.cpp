/*
Sorting algorithms visualization made using olcPixelGameEngine
Copyright (C) 2020 Du�an Erdeljan

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
