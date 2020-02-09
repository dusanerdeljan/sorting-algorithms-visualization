#pragma once
#include "Sort.h"

class InsertionSort : public Sort
{
public:
	std::vector<Animation> SortNumbers(std::vector<int>& numbers) override;
};

