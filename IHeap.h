#pragma once

template<class T> class IHeap{
public:
	virtual T extractMin() = 0;
	virtual void insert(T key) = 0;
	virtual void merge(IHeap<T> *HeapSecond) = 0;


};
