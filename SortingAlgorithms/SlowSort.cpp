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

#include "SlowSort.h"

void SlowSort::SlowSortHelper(std::vector<int>& numbers, size_t i, size_t j, std::vector<Animation>& animations) const
{
	if (i >= j) return;
	size_t mid = (i + j) / 2;
	SlowSortHelper(numbers, i, mid, animations);
	SlowSortHelper(numbers, mid + 1, j, animations);
	animations.push_back(Animation(AnimationType::COMPARE, j, mid));
	if (numbers[j] < numbers[mid])
	{
		animations.push_back(Animation(AnimationType::SWAP, j, mid));
		std::swap(numbers[j], numbers[mid]);
	}
	SlowSortHelper(numbers, i, j - 1, animations);
}

std::vector<Animation> SlowSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	SlowSortHelper(numbers, 0, numbers.size() - 1, animations);
	return animations;
}
