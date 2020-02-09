#pragma once
#include "Sort.h"

class HeapSort : public Sort
{
private:
	void MaxHeapify(std::vector<int>& numbers, int currentLength, int index, std::vector<Animation>& animations) const;
public:
	std::vector<Animation> SortNumbers(std::vector<int>& numbers) override;
};

