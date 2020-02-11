/*
Sorting algorithms visualization made using olcPixelGameEngine
Copyright (C) 2020 Dušan Erdeljan

This file is part of sorting-algorithms-visualization

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "SortingAlgorithmFactory.h"
#include "UIControls.h"
#include <vector>
#include <memory>
#include <random>

#define GREEN olc::Pixel(0, 204, 0)
#define BLUE olc::Pixel(51, 153, 255)
#define DARK_BLUE olc::Pixel(0, 51, 204)
#define VERY_DARK_BLUE olc::Pixel(51, 51, 153)

enum class ApplicationState {ARRAY_GENERATION, SORTING_ANIMATION, ARRAY_SORTED};

class SortingAlgorithms : public olc::PixelGameEngine
{
private:
	std::vector<int> m_NumberArray;
	std::vector<int> m_SortedNumberArray;
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
	Button m_GnomeSortButton;
	Button m_CocktailSortButton;
	Button m_PancakeSortButton;
	Button m_BrickSortButton;
	Button m_CombSortButton;
	Button m_SlowSortButton;
	Slider m_AnimationSpeedSlider;
	Slider m_NumberCountSlider;
	Slider m_FrameDelaySlider;
	Button* m_SelectedSortButton;
	std::vector<Button*> m_Buttons;
	int m_First = -1;
	int m_Second = -1;
	bool m_ShouldDrawArray = true;
	uint32_t m_AnimationsSpeed = 1;
	uint32_t m_NumberCount = 200;
	uint32_t m_BarWidth = 2;
	uint32_t m_BarPadding = 1;
	uint32_t m_TimeBetweenFrames = 0;
	float m_DeltaTime = 0.0f;
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
		m_QuickSortButton(1200, 10, 160, 20, "Quick sort", SortingAlgorithmFactory::Algorithm::QUICK_SORT),
		m_GnomeSortButton(350, 40, 160, 20, "Gnome sort", SortingAlgorithmFactory::Algorithm::GNOME_SORT),
		m_CocktailSortButton(520, 40, 160, 20, "Cocktail sort", SortingAlgorithmFactory::Algorithm::COCKTAIL_SORT),
		m_PancakeSortButton(690, 40, 160, 20, "Pancake sort", SortingAlgorithmFactory::Algorithm::PANCAKE_SORT),
		m_BrickSortButton(860, 40, 160, 20, "Brick sort", SortingAlgorithmFactory::Algorithm::BRICK_SORT),
		m_CombSortButton(1030, 40, 160, 20, "Comb sort", SortingAlgorithmFactory::Algorithm::COMB_SORT),
		m_SlowSortButton(1200, 40, 160, 20, "Slow sort", SortingAlgorithmFactory::Algorithm::SLOW_SORT),
		m_AnimationSpeedSlider(10, 70, 520, 20, "Animations per frame", 1, 20, 1, 8),
		m_NumberCountSlider(560, 70, 720, 20, "Numbers", 40, 400, 200, 8, 10),
		m_FrameDelaySlider(10, 100, 900, 20, "Time between frames (ms)", 0, 2000, 0, 8, 50)
	{
		m_Buttons.push_back(&m_NewArrayButton);
		m_Buttons.push_back(&m_SortButton);
		m_Buttons.push_back(&m_BubbleSortButton);
		m_Buttons.push_back(&m_SelectionSortButton);
		m_Buttons.push_back(&m_InsertionSortButton);
		m_Buttons.push_back(&m_MergeSortButton);
		m_Buttons.push_back(&m_HeapSortButton);
		m_Buttons.push_back(&m_QuickSortButton);
		m_Buttons.push_back(&m_GnomeSortButton);
		m_Buttons.push_back(&m_CocktailSortButton);
		m_Buttons.push_back(&m_PancakeSortButton);
		m_Buttons.push_back(&m_BrickSortButton);
		m_Buttons.push_back(&m_CombSortButton);
		m_Buttons.push_back(&m_SlowSortButton);
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
				DrawNumbers(false, GREEN);
			return true;
		}
		if (m_First != -1 && m_Second != -1)
			RedrawAffectedBars();
		if (m_AnimationIterator->type == AnimationType::COMPARE)
		{
			DrawBar(m_AnimationIterator->firstIndex, false, olc::RED);
			DrawBar(m_AnimationIterator->secondIndex, false, olc::RED);
		}
		else if (m_AnimationIterator->type == AnimationType::SWAP)
		{
			SwapBars(m_AnimationIterator->firstIndex, m_AnimationIterator->secondIndex);
			DrawBar(m_AnimationIterator->firstIndex, false, GREEN);
			DrawBar(m_AnimationIterator->secondIndex, false, GREEN);
		}
		m_First = m_AnimationIterator->firstIndex;
		m_Second = m_AnimationIterator->secondIndex;
		++m_AnimationIterator;
		if (m_AnimationIterator == m_AnimationVector.end())
		{
			m_State = ApplicationState::ARRAY_SORTED;
			m_First = -1;
			m_Second = -1;
		}
		return false;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		DrawUI();
		HandleUIEvents();
		if (m_DeltaTime < m_TimeBetweenFrames)
		{
			m_DeltaTime += (fElapsedTime*1000.0f);
			return true;
		}
		m_DeltaTime = 0.0f;
		for (size_t i = 0; i < m_AnimationsSpeed; i++)
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
			if (m_AnimationSpeedSlider.PointInsideSlider(GetMouseX(), GetMouseY()))
				m_AnimationSpeedSlider.state = Slider::State::SELECTED;
			if (m_NumberCountSlider.PointInsideSlider(GetMouseX(), GetMouseY()) && m_State != ApplicationState::SORTING_ANIMATION)
				m_NumberCountSlider.state = Slider::State::SELECTED;
			if (m_FrameDelaySlider.PointInsideSlider(GetMouseX(), GetMouseY()))
				m_FrameDelaySlider.state = Slider::State::SELECTED;
		}
		if (GetMouse(0).bHeld)
		{
			if (m_AnimationSpeedSlider.PointInsideSlider(GetMouseX(), GetMouseY()))
			{
				m_AnimationSpeedSlider.MoveSlider(GetMouseX());
				m_AnimationsSpeed = m_AnimationSpeedSlider.value;
			}
			if (m_NumberCountSlider.PointInsideSlider(GetMouseX(), GetMouseY()) && m_State != ApplicationState::SORTING_ANIMATION)
			{
				m_NumberCountSlider.MoveSlider(GetMouseX());
				NumberCountSliderValueChanged();
			}
			if (m_FrameDelaySlider.PointInsideSlider(GetMouseX(), GetMouseY()))
			{
				m_FrameDelaySlider.MoveSlider(GetMouseX());
				m_TimeBetweenFrames = m_FrameDelaySlider.value;
			}
		}
		if (GetMouse(0).bReleased)
		{
			if (m_AnimationSpeedSlider.state == Slider::State::SELECTED)
				m_AnimationSpeedSlider.state = Slider::State::NOT_SELECTED;
			if (m_NumberCountSlider.state == Slider::State::SELECTED)
				m_NumberCountSlider.state = Slider::State::NOT_SELECTED;
			if (m_FrameDelaySlider.state == Slider::State::SELECTED)
				m_FrameDelaySlider.state = Slider::State::NOT_SELECTED;
		}
	}
	void NumberCountSliderValueChanged()
	{
		if (m_NumberCount == m_NumberCountSlider.value)
			return;
		m_NumberCount = m_NumberCountSlider.value;
		GenerateArrayButtonAction();
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
		m_AnimationsSpeed = m_AnimationSpeedSlider.value;
		m_TimeBetweenFrames = m_FrameDelaySlider.value;
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
		int screenOffset = 20;
		m_BarWidth = (uint32_t)floor((ScreenWidth() - 2 * screenOffset - (m_NumberCount - 1)*m_BarPadding) / m_NumberCount);
		for (size_t i = 0; i < m_NumberCount; i++)
		{
			std::random_device randomDevice;
			std::mt19937 engine(randomDevice());
			int maxValue = (int)(0.8f * ScreenHeight());
			std::uniform_int_distribution<> numberDistribution(5, maxValue);
			m_NumberArray.push_back(numberDistribution(engine));
		}
		m_SortedNumberArray = m_NumberArray;
		std::sort(m_SortedNumberArray.begin(), m_SortedNumberArray.end());
	}
	void DrawUI()
	{
		for (const Button* btn : m_Buttons)
			DrawButton(*btn);
		DrawSlider(m_AnimationSpeedSlider);
		DrawSlider(m_NumberCountSlider);
		DrawSlider(m_FrameDelaySlider);
	}
	void DrawSlider(const Slider& slider)
	{
		FillRect(slider.x, slider.y, slider.width, slider.height, olc::BLACK);
		DrawString(slider.x, slider.y + slider.height / 2 - 4, slider.text, olc::WHITE);
		DrawLine(slider.x + slider.text.length() * 8 + 16, slider.y + slider.height / 2, slider.x + slider.text.length() * 8 + 16 + 16 * (slider.maxValue - slider.minValue) / slider.notchValue, slider.y + slider.height / 2);
		FillCircle(slider.sliderX, slider.sliderY, slider.sliderRadius, DARK_BLUE);
		DrawString(slider.x + slider.text.length() * 8 + 16 + 16 * (slider.maxValue - slider.minValue)/slider.notchValue + 16, slider.y + slider.height / 2 - 4, std::to_string(slider.value));
	}
	void DrawButton(const Button& button)
	{
		FillRect(button.x, button.y, button.width, button.height, olc::GREY);
		DrawRect(button.x, button.y, button.width, button.height, button.state == Button::State::CHECKED ? GREEN : DARK_BLUE );
		DrawString(button.x + (button.width - button.text.length()*8)/2, button.y + button.height / 2 - 4, button.text, button.state == Button::State::CHECKED ? GREEN : DARK_BLUE);
	}
	void DrawNumbers(bool colorSorted = false, olc::Pixel color = BLUE)
	{
		m_ShouldDrawArray = false;
		for (size_t i = 0; i < m_NumberCount; i++)
		{
			DrawBar(i, colorSorted, color);
		}
	}
	int GetBarPosition(int index)
	{
		int x = (ScreenWidth() - m_NumberCount*(m_BarWidth + m_BarPadding)) / 2;
		return x + (index*(m_BarWidth + m_BarPadding) - m_BarPadding);
	}
	void DrawBar(int index, bool colorSorted = true, olc::Pixel color = BLUE)
	{
		int x = GetBarPosition(index);
		if (colorSorted)
			color = m_SortedNumberArray[index] == m_NumberArray[index] ? VERY_DARK_BLUE : color;
		FillRect(x, ScreenHeight()-m_NumberArray[index]-1, m_BarWidth, m_NumberArray[index], color);
	}
	void SwapBars(int first, int second)
	{
		DrawBar(first, false, olc::BLACK);
		DrawBar(second, false, olc::BLACK);
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