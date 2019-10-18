#pragma once
#include "pch.h"
#include "IntArray.hpp"

IntArray::IntArray(int size, std::string name) {
	int i = 0;
	this->name = name;
	printf("construite!%s\n", this->name.c_str());
	maxSize = size;
	//c old school
	//data = (int*)malloc(size *sizeof(int));
	//memset(data,0,size*sizeof(int));

	//c new school
	//data = (int*)calloc(size, sizeof(int));
	//c++
	data = new int[size];
	for (int i = 0; i < size; ++i) data[i] = 0;
}

void IntArray::Ensure(int size) {
	if (size > this->maxSize) {
		int * newdata = new int[size];
		for (int i = 0; i < size; i++) { newdata[i] = 0; }
		for (int i = 0; i < size; i++) { newdata[i] = this->data[i]; }

		delete this->data;
		this->data = newdata;
		this->maxSize = size;

	}
}

void IntArray::set(int pos, int elem) {
	Ensure(pos+1);
	data[pos] = elem;
	if (pos >= curSize)
		curSize = pos + 1;
}

void IntArray::set_unsafe(int pos, int elem) {
	data[pos] = elem;
	if (pos + 1 > curSize)
		curSize = pos + 1;
}

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

void IntArray::insert(int pos, int elem) {
	Ensure((pos >= curSize) ? (pos + 1) : (curSize + 1));
	for (int i = curSize; i > pos; i--)
	{
		data[i] = data[i - 1];
	}
	data[pos] = elem;
	if (pos < curSize)
		curSize += 1;
	else if (pos >= curSize)
		curSize = pos + 1;
}

int IntArray::searchposition(int elem) {
	for (int i = curSize-1; i >= 0; i--) {
		if (elem >= this->data[i]) {
			return i+1;
		}
		else if (i == 0)
			return 0;
		
	}
	return curSize;
}

bool IntArray::Remove(int val) {
	int Index = -1;
	for (int i = 0; i < curSize; i++) {
		if (data[i] == val) {
			Index = i;
			break;
		}
		
	}
	if (Index == -1)
		return false;
	for (int i = Index; i < curSize-1; i++) {
		data[i] = data[i + 1];
		
	}
	data[curSize - 1] = 0;
	curSize--;

}

int IntArray::searchpositionBIS(int elem, int indexmax) {
	for (int i = 0; i <= indexmax; i++) {
		if (elem <= this->data[i]) {
			return i-1;
		}
		else if (i == indexmax)
			return indexmax;

	}
	return curSize;
}


