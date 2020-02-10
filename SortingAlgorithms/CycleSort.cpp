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

#include "CycleSort.h"

void CycleSort::Swap(std::vector<int>& numbers, size_t & first, size_t & second)
{
	std::swap(numbers[first], numbers[second]);
	size_t temp = first;
	first = second;
	second = temp;
}

std::vector<Animation> CycleSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	for (size_t start = 0; start <= numbers.size()-2; start++)
	{
		size_t startPosition = start;
		size_t position = start;
		for (size_t i = start + 1; i < numbers.size(); i++)
		{
			animations.push_back(Animation(AnimationType::COMPARE, i, startPosition));
			if (numbers[i] < numbers[startPosition])
				position++;
		}
		if (position == startPosition) continue;
		while (numbers[startPosition] == numbers[position])
		{
			animations.push_back(Animation(AnimationType::COMPARE, startPosition, position));
			position++;
		}
		while (position != startPosition)
		{
			animations.push_back(Animation(AnimationType::SWAP, startPosition, position));
			Swap(numbers, position, startPosition);
		}
		while (position != startPosition)
		{
			position = startPosition;
			for (size_t i = start + 1; i < numbers.size(); i++)
			{
				animations.push_back(Animation(AnimationType::COMPARE, position, startPosition));
				if (numbers[i] < numbers[startPosition])
					position++;
			}
			while (numbers[startPosition] == numbers[position])
			{
				animations.push_back(Animation(AnimationType::COMPARE, startPosition, position));
				position++;
			}
			animations.push_back(Animation(AnimationType::COMPARE, startPosition, position));
			if (numbers[startPosition] != numbers[position])
			{
				animations.push_back(Animation(AnimationType::SWAP, startPosition, position));
				Swap(numbers, position, startPosition);
			}
		}
	}
	return animations;
}
