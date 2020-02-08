#pragma once
#include "Sort.h"

class BubbleSort : public Sort
{
public:
	std::vector<Animation> SortNumbers(std::vector<int>& numbers) override;
};

