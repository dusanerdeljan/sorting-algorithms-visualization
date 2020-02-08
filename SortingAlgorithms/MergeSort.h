#pragma once
#include "Sort.h"

class MergeSort : public Sort
{
private:
	void Merge(std::vector<int>& numbers, int left, int mid, int right, std::vector<Animation>& animations) const;
	void MergeSortHelper(std::vector<int>& numbers, int left, int right, std::vector<Animation>& animations) const;
public:
	std::vector<Animation> SortNumbers(std::vector<int>& numbers) override;
};

