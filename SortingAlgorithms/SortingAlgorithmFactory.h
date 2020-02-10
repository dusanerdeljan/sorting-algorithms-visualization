#pragma once
#include "Sort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "GnomeSort.h"
#include "CocktailSort.h"
#include "PancakeSort.h"
#include "BrickSort.h"
#include "CombSort.h"
#include <memory>

class SortingAlgorithmFactory
{
public:
	enum class Algorithm {BUBBLE_SORT, SELECTION_SORT, INSERTION_SORT, MERGE_SORT, QUICK_SORT, HEAP_SORT, 
		GNOME_SORT, COCKTAIL_SORT, PANCAKE_SORT, BRICK_SORT, COMB_SORT};
	static std::unique_ptr<Sort> GetSortingAlgorithm(SortingAlgorithmFactory::Algorithm algorithmType);
};

