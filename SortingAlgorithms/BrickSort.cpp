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

#include "BrickSort.h"

std::vector<Animation> BrickSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (size_t i = 1; i <= numbers.size() - 2; i = i + 2)
		{
			animations.push_back(Animation(AnimationType::COMPARE, i, i + 1));
			if (numbers[i] > numbers[i + 1])
			{
				animations.push_back(Animation(AnimationType::SWAP, i, i + 1));
				std::swap(numbers[i], numbers[i + 1]);
				sorted = false;
			}
		} 
		for (size_t i = 0; i <= numbers.size() - 2; i = i + 2)
		{
			animations.push_back(Animation(AnimationType::COMPARE, i, i + 1));
			if (numbers[i] > numbers[i + 1])
			{
				animations.push_back(Animation(AnimationType::SWAP, i, i + 1));
				std::swap(numbers[i], numbers[i + 1]);
				sorted = false;
			}
		}
	}
	return animations;
}
