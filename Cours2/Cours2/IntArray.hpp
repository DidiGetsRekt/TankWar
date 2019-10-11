#pragma once
#include "pch.h"

#include <cstdio>
#include <cstdlib>
#include <string>

class IntArray {
public:
	static int TEST;
	std::string name;
	int * data;
	int maxSize;
	int curSize = 0;

	IntArray(int size, std::string name) {
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
	};
	

	~IntArray() {
		printf("détruite!%s\n", this->name.c_str());
	};

	void Ensure(int size) {
		if (size > this->maxSize) {
			int * newdata = new int[size];
			for (int i = 0; i < size; i++) { newdata[i] =0; }
			for(int i = 0; i < size; i++){ newdata[i] = this->data[i];  }
			
			delete this->data;
			this->data = newdata;
			this->maxSize = size;

		}
	}
	void set(int pos, int elem) {
		Ensure(pos);
		data[pos] = elem;
		if (pos + 1 > curSize)
		curSize = pos+1;
	}
	void set_unsafe(int pos, int elem) {
		data[pos] = elem;
		if(pos+1 > curSize)
		curSize = pos+1;
	}
	void push_back(int elem);

	void push_first(int elem);

	void insert(int pos, int elem) {
		Ensure(curSize + 1);
		for (int i = curSize; i > pos; i--)
		{
			data[i] = data[i - 1];
		}
		data[pos] = elem;
		curSize += 1;
	}

	int operator()(int pos) {
		Ensure(pos);
		return data[pos];
	}
	int operator[](int pos) {
		Ensure(pos);
		return data[pos];
	}
};