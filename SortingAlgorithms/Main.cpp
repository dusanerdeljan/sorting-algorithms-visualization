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
	enum class State {CHECKED, UNCHECKED};

	std::string text;
	uint32_t width;
	uint32_t height;
	uint32_t x;
	uint32_t y;
	State state;
	Button(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string text, Button::State state = Button::State::UNCHECKED)
		: text(text), width(w), height(h), x(x), y(y), state(state) { }
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
	std::vector<Button*> m_Buttons;
	int m_First = -1;
	int m_Second = -1;
	bool m_ShouldDrawArray = true;
	SortingAlgorithmFactory::Algorithm m_SortingAlgorithm = SortingAlgorithmFactory::Algorithm::HEAP_SORT;
	ApplicationState m_State = ApplicationState::ARRAY_GENERATION;
public:
	SortingAlgorithms()
		: m_NewArrayButton(10, 10, 160, 20, "Generate new array"),
		m_SortButton(180, 10, 160, 20, "Sort!")
	{
		m_Buttons.push_back(&m_NewArrayButton);
		m_Buttons.push_back(&m_SortButton);
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
				DrawNumbers(olc::GREEN);
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
			for (const Button* btn : m_Buttons)
			{
				if (btn->PointInsideButton(GetMouseX(), GetMouseY()))
				{
					if (btn == &m_NewArrayButton)
					{
						if (m_State == ApplicationState::SORTING_ANIMATION)
							return;
						GenerateArray();
						Clear(olc::BLACK);
						m_ShouldDrawArray = true;
						m_State = ApplicationState::ARRAY_GENERATION;
					}
					else if (btn == &m_SortButton)
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
				}
			}
		}
	}
	void GenerateArray()
	{
		m_NumberArray.clear();
		// Generate random numbers array
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
		DrawRect(button.x, button.y, button.width, button.height, olc::DARK_GREEN);
		DrawString(button.x + (button.width - button.text.length()*8)/2, button.y + button.height / 2 - 4, button.text);
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
	if (demo.Construct(1366, 768, 1, 1))
		demo.Start();
	return 0;
}