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
#include "Sort.h"

class MergeSort : public Sort
{
private:
	void Merge(std::vector<int>& numbers, int left, int mid, int right, std::vector<Animation>& animations) const;
	void MergeSortHelper(std::vector<int>& numbers, int left, int right, std::vector<Animation>& animations) const;
public:
	std::vector<Animation> SortNumbers(std::vector<int>& numbers) override;
};

