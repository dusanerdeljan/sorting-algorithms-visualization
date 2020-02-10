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

#include "CombSort.h"

std::vector<Animation> CombSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	auto GetNextGap = [](size_t gap)
	{
		gap = (gap * 10) / 13;
		return (gap < 1) ? 1 : gap;
	};
	size_t gap = numbers.size();
	bool swapped = true;
	while (gap != 1 || swapped == true)
	{
		gap = GetNextGap(gap);
		swapped = false;
		for (size_t i = 0; i < numbers.size() - gap; i++)
		{
			animations.push_back(Animation(AnimationType::COMPARE, i, i + gap));
			if (numbers[i] > numbers[i + gap])
			{
				animations.push_back(Animation(AnimationType::SWAP, i, i + gap));
				std::swap(numbers[i], numbers[i + gap]);
				swapped = true;
			}
		}
	}
	return animations;
}
