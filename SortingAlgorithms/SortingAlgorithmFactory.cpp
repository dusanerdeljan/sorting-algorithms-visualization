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

#include "SortingAlgorithmFactory.h"

std::unique_ptr<Sort> SortingAlgorithmFactory::GetSortingAlgorithm(SortingAlgorithmFactory::Algorithm algorithmType)
{
	switch (algorithmType)
	{
	case SortingAlgorithmFactory::Algorithm::BUBBLE_SORT:
		return std::make_unique<BubbleSort>();
	case SortingAlgorithmFactory::Algorithm::SELECTION_SORT:
		return std::make_unique<SelectionSort>();
	case SortingAlgorithmFactory::Algorithm::INSERTION_SORT:
		return std::make_unique<InsertionSort>();
	case SortingAlgorithmFactory::Algorithm::MERGE_SORT:
		return std::make_unique<MergeSort>();
	case SortingAlgorithmFactory::Algorithm::QUICK_SORT:
		return std::make_unique<QuickSort>();
	case SortingAlgorithmFactory::Algorithm::HEAP_SORT:
		return std::make_unique<HeapSort>();
	case SortingAlgorithmFactory::Algorithm::GNOME_SORT:
		return std::make_unique<GnomeSort>();
	case SortingAlgorithmFactory::Algorithm::COCKTAIL_SORT:
		return std::make_unique<CocktailSort>();
	case SortingAlgorithmFactory::Algorithm::PANCAKE_SORT:
		return std::make_unique<PancakeSort>();
	default:
		return std::make_unique<MergeSort>();
	}
}
