#pragma once
#include <vector>
#include "IHeap.h"


template <class T, class Heap> class Interface {
private:
	std::vector <Heap*> heapArray;
public:
	size_t numberOfHeaps()
	{
		return heapArray.size();
	}
	void AddHeap(T key) {
		heapArray.push_back(new Heap(key));
	}

	void Insert(size_t index, T key)
	{
		heapArray[index]->insert(key);
	}

	T ExtractMin(size_t index)
	{
		return heapArray[index]->extractMin();
	}

	void Meld(size_t index1, size_t index2)
	{
		heapArray[index1]->merge(heapArray[index2]);
		heapArray[index2] = heapArray.back();
		heapArray.pop_back();
	}
	bool Empty(size_t index)
	{
		return heapArray[index]->empty();
	}
};