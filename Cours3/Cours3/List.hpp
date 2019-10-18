#pragma once

template<typename Type>
class List {
public:
	Type elem;
	List<Type> * next = nullptr;
	List(const Type & elem) {
		this->elem = elem;
	}
	int Length() {
		if (next == nullptr)
			return 1;
		else return next->Length()+1;
	}
	void Append(const Type & elem) {
		if (next == nullptr)
			next = new List(elem);
		else
			next->Append(elem);
	}
	List<Type>* Concat(const Type & elem) {
		List<Type>* nyu = new List(elem);
		nyu->next = this;
		return nyu;
	}
	List<Type>* Remove(const Type & elem) {
		if (elem == this->elem) {
			auto suite = next;
			this->next = nullptr;
			delete this;
			if (suite != 0)
				return suite->Remove(elem);
			else return nullptr;
		}
			
		else {
			if (next)
				next = next->Remove(elem);
			return this;

		}
	}
	bool Contains(const Type & elem) {
		if (this->elem == elem)
			return true; 
		else if (next == nullptr)
			return false;
		else
			next->Contains(elem);
	}
};

typedef List<int> IntList;