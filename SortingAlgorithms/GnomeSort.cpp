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

#include "GnomeSort.h"

std::vector<Animation> GnomeSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	uint32_t currentIndex = 0;
	while (currentIndex < numbers.size())
	{
		if (currentIndex == 0) ++currentIndex;
		animations.push_back(Animation(AnimationType::COMPARE, currentIndex, currentIndex - 1));
		if (numbers[currentIndex] >= numbers[currentIndex - 1])	++currentIndex;
		else
		{
			animations.push_back(Animation(AnimationType::SWAP, currentIndex, currentIndex - 1));
			std::swap(numbers[currentIndex], numbers[currentIndex - 1]);
			--currentIndex;
		}
	}
	return animations;
}
