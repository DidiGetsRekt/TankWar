#pragma once

template<typename Type>
class List {
public:
	Type elem;
	List<Type> * next = nullptr;
	List(const Type & elem) {
		this->elem = elem;
	}
};

typedef List<int> IntList;