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
