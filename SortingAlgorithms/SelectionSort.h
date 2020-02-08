#pragma once
#include "Sort.h"

class SelectionSort : public Sort
{
public:
	std::vector<Animation> SortNumbers(std::vector<int>& numbers) override;
};

