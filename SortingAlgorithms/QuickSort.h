#pragma once
#include "Sort.h"

class QuickSort : public Sort
{
private:
	int Partition(std::vector<int>& numbers, int low, int high, std::vector<Animation>& animations) const;
	void QuickSortHelper(std::vector<int>& numbers, int low, int high, std::vector<Animation>& animations) const;
public:
	std::vector<Animation> SortNumbers(std::vector<int>& numbers) override;
};

