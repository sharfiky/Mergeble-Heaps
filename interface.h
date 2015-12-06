#pragma once
#include <vector>
#include "IHeap.h"


template <class T> class Interface {
private:
	std::vector <IHeap<int>> heapArray;
public:
	void AddHeap(T key) {
		heapArray.push_back(makeVertex(key));
	}

	void Insert(size_t index, T key)
	{
		merge(heapArray[index], makeVertex(key));
	}

	void ExtractMin(size_t index)
	{
		heapArray[index].extractMin();
	}

	void Meld(size_t index1, size_t index2)
	{
		merge(heapArray[index1], heapArray[index2]);
	}
};