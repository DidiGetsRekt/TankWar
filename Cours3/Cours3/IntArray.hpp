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

	void swap(int pos1, int pos2) {
		int temp = data[pos1];
		data[pos1] = data[pos2];
		data[pos2] = temp;
	}

	void InSort() {
		for (int i = 0; i < curSize; i++) {
			int j = i;
			while (j > 0 && (data[j] < data[j - 1])) {
				swap(j, j - 1);
				j = j - 1;
			}
		}
	}
	int searchpositionBIS(int elem, int indexmax);
	void OneSort() {
		int curSorted = 0;
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
			int pos = searchpositionBIS(data[i], curSorted);
			insert(pos, data[i]);
			curSorted++;
		}
		

	}
	int BinarySearch(int key) {
		return _BinarySearch(key, 0, curSize);
	}
	int _BinarySearch(int key, int start, int end) {
		int piv = (end + start) / 2;
		printf("key: %d start: %d end: %d \n", key, data[start], data[end]);
		if (end == 0)
			return 0;
		if((key == data[piv]))
			return piv;
		else if (key > data[piv] && key < data[piv+1])
			return (piv+1);
		else if (key > data[piv])
			return _BinarySearch(key, piv, end);
		else if (key < data[piv])
			return _BinarySearch(key, 0, piv);
		return 0;
	}
	
};