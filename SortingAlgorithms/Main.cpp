#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Sort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include <vector>
#include <memory>
#include <random>

#define NUM_ELEMENTS 100
#define BAR_WIDTH 10
#define BAR_PADDING 2

class SortingAlgorithms : public olc::PixelGameEngine
{
private:
	std::vector<int> m_NumberArray;
	std::unique_ptr<Sort> m_Sort;
	std::vector<Animation>::iterator m_AnimationIterator;
	std::vector<Animation> m_AnimationVector;
public:
	SortingAlgorithms()
	{
		sAppName = "Sorting algorithms visualization";
	}
public:
	bool OnUserCreate() override
	{
		// Generate random numbers array
		for (size_t i = 0; i < NUM_ELEMENTS; i++)
		{
			std::random_device randomDevice;
			std::mt19937 engine(randomDevice());
			std::uniform_int_distribution<> numberDistribution(5, 750);
			m_NumberArray.push_back(numberDistribution(engine));
		}
		m_Sort = std::make_unique<MergeSort>();
		std::vector<int> copy(m_NumberArray);
		m_AnimationVector = m_Sort->SortNumbers(copy);
		m_AnimationIterator = m_AnimationVector.begin();
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		if (m_AnimationIterator == m_AnimationVector.end())
		{
			DrawNumbers(olc::GREEN);
			return true;
		} 
		DrawNumbers();
		if (m_AnimationIterator->type == AnimationType::COMPARE)
		{
			DrawBar(m_AnimationIterator->firstIndex, olc::RED);
			DrawBar(m_AnimationIterator->secondIndex, olc::RED);
		}
		else
		{
			std::swap(m_NumberArray[m_AnimationIterator->firstIndex], m_NumberArray[m_AnimationIterator->secondIndex]);
			DrawBar(m_AnimationIterator->firstIndex, olc::GREEN);
			DrawBar(m_AnimationIterator->secondIndex, olc::GREEN);
		}
		++m_AnimationIterator;
		return true;
	}
private:
	void DrawNumbers(olc::Pixel color = olc::BLUE)
	{
		for (size_t i = 0; i < NUM_ELEMENTS; i++)
		{
			DrawBar(i, color);
		}
	}
	int GetBarPosition(int index)
	{
		int x = (ScreenWidth() - NUM_ELEMENTS*(BAR_WIDTH + BAR_PADDING)) / 2;
		return x + (index*(BAR_WIDTH + BAR_PADDING) - BAR_PADDING);
	}
	void DrawBar(int index, olc::Pixel color = olc::BLUE)
	{
		int x = GetBarPosition(index);
		FillRect(x, 0, BAR_WIDTH, m_NumberArray[index], color);
	}
};
int main()
{
	SortingAlgorithms demo;
	if (demo.Construct(1366, 768, 1, 1))
		demo.Start();
	return 0;
}