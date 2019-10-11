#pragma once
#include "pch.h"
#include "IntArray.hpp"

void IntArray::push_back(int elem) {
	Ensure(curSize + 1);

	data[curSize] = elem;
	curSize += 1;
}
void  IntArray::push_first(int elem) {
	Ensure(curSize + 1);

	for (int i = curSize; i > 0; i--)
	{
		data[i] = data[i - 1];
	}
	data[0] = elem;
	curSize += 1;
}