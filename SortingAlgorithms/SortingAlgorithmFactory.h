#pragma once
#include "Sort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include <memory>

class SortingAlgorithmFactory
{
public:
	enum class Algorithm {BUBBLE_SORT, SELECTION_SORT, INSERTION_SORT, MERGE_SORT, QUICK_SORT, HEAP_SORT};
	static std::unique_ptr<Sort> GetSortingAlgorithm(SortingAlgorithmFactory::Algorithm algorithmType);
};

