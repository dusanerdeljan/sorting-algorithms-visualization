#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "SortingAlgorithmFactory.h"
#include <vector>
#include <memory>
#include <random>
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

#define NUM_ELEMENTS 200
#define BAR_WIDTH 4
#define BAR_PADDING 2
#define ANIMATIONS_PER_FRAME 10

struct Button
{
	enum class State {UNCHECKED = 0, CHECKED};

	std::string text;
	uint32_t width;
	uint32_t height;
	uint32_t x;
	uint32_t y;
	State state;
	SortingAlgorithmFactory::Algorithm algorithm;
	Button(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string text, 
		SortingAlgorithmFactory::Algorithm algorithm = SortingAlgorithmFactory::Algorithm::MERGE_SORT, 
		Button::State state = Button::State::UNCHECKED)
		: text(text), width(w), height(h), x(x), y(y), state(state), algorithm(algorithm) { }
	bool PointInsideButton(uint32_t x, uint32_t y) const
	{
		return (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height);
	}
};

enum class ApplicationState {ARRAY_GENERATION, SORTING_ANIMATION, ARRAY_SORTED};

class SortingAlgorithms : public olc::PixelGameEngine
{
private:
	std::vector<int> m_NumberArray;
	std::unique_ptr<Sort> m_Sort;
	std::vector<Animation>::iterator m_AnimationIterator;
	std::vector<Animation> m_AnimationVector;
	Button m_NewArrayButton;
	Button m_SortButton;
	Button m_BubbleSortButton;
	Button m_SelectionSortButton;
	Button m_InsertionSortButton;
	Button m_MergeSortButton;
	Button m_HeapSortButton;
	Button m_QuickSortButton;
	Button* m_SelectedSortButton;
	std::vector<Button*> m_Buttons;
	int m_First = -1;
	int m_Second = -1;
	bool m_ShouldDrawArray = true;
	SortingAlgorithmFactory::Algorithm m_SortingAlgorithm = SortingAlgorithmFactory::Algorithm::MERGE_SORT;
	ApplicationState m_State = ApplicationState::ARRAY_GENERATION;
public:
	SortingAlgorithms()
		: m_NewArrayButton(10, 10, 160, 20, "Generate new array"),
		m_SortButton(180, 10, 160, 20, "Sort!"),
		m_BubbleSortButton(350, 10, 160, 20, "Bubble sort", SortingAlgorithmFactory::Algorithm::BUBBLE_SORT),
		m_SelectionSortButton(520, 10, 160, 20, "Selection sort", SortingAlgorithmFactory::Algorithm::SELECTION_SORT),
		m_InsertionSortButton(690, 10, 160, 20, "Insertion sort", SortingAlgorithmFactory::Algorithm::INSERTION_SORT),
		m_MergeSortButton(860, 10, 160, 20, "Merge sort", SortingAlgorithmFactory::Algorithm::MERGE_SORT, Button::State::CHECKED),
		m_HeapSortButton(1030, 10, 160, 20, "Heap sort", SortingAlgorithmFactory::Algorithm::HEAP_SORT),
		m_QuickSortButton(1200, 10, 160, 20, "Quick sort", SortingAlgorithmFactory::Algorithm::QUICK_SORT)
	{
		m_Buttons.push_back(&m_NewArrayButton);
		m_Buttons.push_back(&m_SortButton);
		m_Buttons.push_back(&m_BubbleSortButton);
		m_Buttons.push_back(&m_SelectionSortButton);
		m_Buttons.push_back(&m_InsertionSortButton);
		m_Buttons.push_back(&m_MergeSortButton);
		m_Buttons.push_back(&m_HeapSortButton);
		m_Buttons.push_back(&m_QuickSortButton);
		m_SelectedSortButton = &m_MergeSortButton;
		sAppName = "Sorting algorithms visualization";
	}
public:
	bool OnUserCreate() override
	{
		GenerateArray();
		return true;
	}
	bool AnimationFrame()
	{
		if (m_State == ApplicationState::ARRAY_GENERATION)
		{
			if (m_ShouldDrawArray)
				DrawNumbers();
			return true;
		}
		if (m_State == ApplicationState::ARRAY_SORTED)
		{
			if (m_ShouldDrawArray)
				DrawNumbers(olc::DARK_GREEN);
			return true;
		}
		if (m_First != -1 && m_Second != -1)
			RedrawAffectedBars();
		if (m_AnimationIterator->type == AnimationType::COMPARE)
		{
			DrawBar(m_AnimationIterator->firstIndex, olc::RED);
			DrawBar(m_AnimationIterator->secondIndex, olc::RED);
		}
		else
		{
			SwapBars(m_AnimationIterator->firstIndex, m_AnimationIterator->secondIndex);
			DrawBar(m_AnimationIterator->firstIndex, olc::GREEN);
			DrawBar(m_AnimationIterator->secondIndex, olc::GREEN);
		}
		m_First = m_AnimationIterator->firstIndex;
		m_Second = m_AnimationIterator->secondIndex;
		++m_AnimationIterator;
		if (m_AnimationIterator == m_AnimationVector.end())
			m_State = ApplicationState::ARRAY_SORTED;
		return false;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		DrawUI();
		HandleUIEvents();
		for (size_t i = 0; i < ANIMATIONS_PER_FRAME; i++)
		{
			if (AnimationFrame())
				return true;
		}
		return true;
	}
private:
	void HandleUIEvents()
	{
		if (GetMouse(0).bPressed)
		{
			for (Button* btn : m_Buttons)
			{
				if (btn->PointInsideButton(GetMouseX(), GetMouseY()))
				{
					if (btn == &m_NewArrayButton)
						GenerateArrayButtonAction();
					else if (btn == &m_SortButton)
						SortButtonAction();
					else
					{
						m_SelectedSortButton->state = Button::State::UNCHECKED;
						btn->state = Button::State::CHECKED;
						m_SelectedSortButton = btn;
						m_SortingAlgorithm = btn->algorithm;
					}
				}
			}
		}
	}
	void GenerateArrayButtonAction()
	{
		if (m_State == ApplicationState::SORTING_ANIMATION)
			return;
		GenerateArray();
		Clear(olc::BLACK);
		m_ShouldDrawArray = true;
		m_State = ApplicationState::ARRAY_GENERATION;
	}
	void SortButtonAction()
	{
		if (m_State != ApplicationState::ARRAY_GENERATION)
			return;
		m_Sort = SortingAlgorithmFactory::GetSortingAlgorithm(m_SortingAlgorithm);
		m_State = ApplicationState::SORTING_ANIMATION;
		m_ShouldDrawArray = true;
		std::vector<int> copy(m_NumberArray);
		m_AnimationVector = m_Sort->SortNumbers(copy);
		m_AnimationIterator = m_AnimationVector.begin();
	}
	void GenerateArray()
	{
		m_NumberArray.clear();
		for (size_t i = 0; i < NUM_ELEMENTS; i++)
		{
			std::random_device randomDevice;
			std::mt19937 engine(randomDevice());
			int maxValue = (int)(0.8f * ScreenHeight());
			std::uniform_int_distribution<> numberDistribution(5, maxValue);
			m_NumberArray.push_back(numberDistribution(engine));
		}
	}
	void DrawUI()
	{
		for (const Button* btn : m_Buttons)
			DrawButton(*btn);
	}
	void DrawButton(const Button& button)
	{
		FillRect(button.x, button.y, button.width, button.height, olc::GREY);
		DrawRect(button.x, button.y, button.width, button.height, button.state == Button::State::CHECKED ? olc::DARK_GREEN : olc::BLUE );
		DrawString(button.x + (button.width - button.text.length()*8)/2, button.y + button.height / 2 - 4, button.text, button.state == Button::State::CHECKED ? olc::DARK_GREEN : olc::BLUE);
	}
	void DrawNumbers(olc::Pixel color = olc::BLUE)
	{
		m_ShouldDrawArray = false;
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
		FillRect(x, ScreenHeight()-m_NumberArray[index]-1, BAR_WIDTH, m_NumberArray[index], color);
	}
	void SwapBars(int first, int second)
	{
		DrawBar(first, olc::BLACK);
		DrawBar(second, olc::BLACK);
		std::swap(m_NumberArray[first], m_NumberArray[second]);
		DrawBar(first);
		DrawBar(second);
	}
	void RedrawAffectedBars()
	{
		DrawBar(m_First);
		DrawBar(m_Second);
	}
};
int main()
{
	SortingAlgorithms demo;
	if (demo.Construct(1370, 768, 1, 1))
		demo.Start();
	return 0;
}