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

	IntArray(int size, std::string name="");;
	

	~IntArray() {
		printf("détruite!%s\n", this->name.c_str());
	};

	void Ensure(int size);
	void set(int pos, int elem);
	void set_unsafe(int pos, int elem);
	void push_back(int elem);

	void push_first(int elem);

	void insert(int pos, int elem);

	int operator()(int pos) {
		Ensure(pos);
		
		return data[pos];
	}
	int & operator[](int pos) {
		Ensure(pos+1);
		return data[pos];
	}

	int searchposition(int elem);
	bool Remove(int val);
	bool RemoveAll() {
		curSize = 0;
	}
	void FillWithRandom(int nbElem) {
		Ensure(nbElem);
		for (int i = 0; i < nbElem; ++i) {
			int val = std::rand();
			set(i, val);
		}
	}
	void sort() {
		IntArray nuSize(curSize);
		for (int i = 0; i < curSize; i++) {
			/*for (int j = 0; j <= nuSize.curSize; j++) {
				if (i == 0) {
					nuSize[j] = data[i];
					curSize++;
				}
					
				else if (nuSize[j] < data[i])
				{
					nuSize.insert(j, data[i]);
				}
				else if (j == nuSize.curSize - 1)
				{
					nuSize[j] = data[i];
					curSize++;
				}}*/
			int pos = nuSize.searchposition(data[i]);
			nuSize.insert(nuSize.searchposition(data[i]), data[i]);
			
		}
		for(int i = 0; i < curSize; i++) {
			data[i] = nuSize[i];
		}

	}
};