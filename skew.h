#pragma once

#include <vector>
#include "IHeap.h"
#include "comparators.h"



template <class T> class SkewNode {
public:
	SkewNode *rightNode;
	SkewNode *leftNode;
	T key;
	SkewNode():rightNode(NULL), leftNode(NULL), key(NULL) {}
	SkewNode(T key) : rightNode(NULL), leftNode(NULL), key(key) {}
	SkewNode(const SkewNode<T> *b) : rightNode(b->rightNode), leftNode(b->leftNode),
		key(key) {}
};

template<class T> SkewNode<T>* _Merge(SkewNode<T>* root_1, SkewNode<T>* root_2)
{
	SkewNode<T>* firstRoot = root_1;
	SkewNode<T>* secondRoot = root_2;

	if (firstRoot == NULL)
		return secondRoot;

	else if (secondRoot == NULL)
		return firstRoot;

	if (!Less(firstRoot->key, secondRoot->key))
	{
		SkewNode<T>* temp = firstRoot;
		firstRoot = secondRoot;
		secondRoot = temp;
	}

	SkewNode<T>* tempHeap = firstRoot->rightNode;
	firstRoot->rightNode = firstRoot->leftNode;
	firstRoot->leftNode = _Merge(secondRoot, tempHeap);
	return firstRoot;
}

template <class T> class CSkewHeap :public IHeap<T>{
private:
	SkewNode<T> *head;
	int sizeOfHeap;
public:
	CSkewHeap():head(NULL), sizeOfHeap(0){}
	CSkewHeap(T key): head(NULL), sizeOfHeap(1) {
		head = new SkewNode<T>(key);
	}

	bool empty()
	{
		return sizeOfHeap == 0;
	}

	T extractMin()
	{
		T tmp = head->key;
		head = _Merge(head->rightNode, head->leftNode);
		sizeOfHeap--;
		return tmp;
	}
	void insert(T key)
	{
		SkewNode<T> *tmp = new SkewNode<T>(key);
		head = _Merge(head, tmp);
		sizeOfHeap++;
	}
	void merge(IHeap<T>* HeapSecond)
	{
		sizeOfHeap += dynamic_cast<CSkewHeap<T>*> (HeapSecond)->sizeOfHeap;
		head = _Merge(head, dynamic_cast<CSkewHeap<T>*> (HeapSecond)->head);
	}
};