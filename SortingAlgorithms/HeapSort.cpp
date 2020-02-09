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

#include "HeapSort.h"

void HeapSort::MaxHeapify(std::vector<int>& numbers, int currentLength, int index, std::vector<Animation>& animations) const
{
	int largest = index;
	int leftChild = 2 * index + 1;
	int rightChild = 2 * index + 2;
	if (leftChild < currentLength)
	{
		animations.push_back(Animation(AnimationType::COMPARE, leftChild, largest));
		if (numbers[leftChild] > numbers[largest]) largest = leftChild;
	}
	if (rightChild < currentLength)
	{
		animations.push_back(Animation(AnimationType::COMPARE, rightChild, largest));
		if (numbers[rightChild] > numbers[largest]) largest = rightChild;
	}
	if (largest != index)
	{
		std::swap(numbers[index], numbers[largest]);
		animations.push_back(Animation(AnimationType::SWAP, index, largest));
		MaxHeapify(numbers, currentLength, largest, animations);
	}
}

std::vector<Animation> HeapSort::SortNumbers(std::vector<int>& numbers)
{
	std::vector<Animation> animations;
	for (int i = numbers.size() / 2 - 1; i >= 0; i--)
		MaxHeapify(numbers, numbers.size(), i, animations);
	for (int i = numbers.size() - 1; i >= 0; i--)
	{
		std::swap(numbers[0], numbers[i]);
		animations.push_back(Animation(AnimationType::SWAP, 0, i));
		MaxHeapify(numbers, i, 0, animations);
	}
	return animations;
}
