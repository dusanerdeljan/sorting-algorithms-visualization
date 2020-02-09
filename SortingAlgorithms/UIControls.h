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

#pragma once
#include "SortingAlgorithmFactory.h"

struct Button
{
	enum class State { UNCHECKED = 0, CHECKED };

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
		: text(text), width(w), height(h), x(x), y(y), state(state), algorithm(algorithm)
	{
	}
	bool PointInsideButton(uint32_t x, uint32_t y) const
	{
		return (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height);
	}
};

struct Slider
{
	enum class State { NOT_SELECTED, SELECTED };

	uint32_t sliderX;
	uint32_t sliderY;
	uint32_t sliderRadius;
	std::string text;
	uint32_t width;
	uint32_t height;
	uint32_t x;
	uint32_t y;
	int value;
	int minValue;
	int maxValue;
	int notchValue;
	State state;
	Slider(uint32_t x, uint32_t y, uint32_t w, uint32_t h, std::string text, int minValue, int maxValue, int value, uint32_t sliderRadius, int notchValue=1)
		: text(text), width(w), height(h), x(x), y(y), value(value), minValue(minValue), maxValue(maxValue), sliderRadius(sliderRadius), notchValue(notchValue), state(Slider::State::NOT_SELECTED)
	{
		sliderY = y + height / 2;
		sliderX = x + text.length() * 8 + 16 + ((value - minValue)/notchValue) * 16;
	}
	bool PointInsideSlider(uint32_t x, uint32_t y) const
	{
		return (x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height);
	}
	void MoveSlider(uint32_t mouseX)
	{
		uint32_t beginX = x + text.length() * 8 + 16;
		uint32_t endX = x + text.length() * 8 + (maxValue - minValue)/notchValue * 16 + 16;
		sliderX = std::min(std::max(beginX, mouseX), endX);
		value = (int)round(((sliderX - beginX) / 16.0)*notchValue + minValue);
	}
};
