#pragma once

#include <vector>
#include "IHeap.h"
#include "comparators.h"

template <class T> class LeftistNode  {
public:
	LeftistNode *rightNode;
	LeftistNode *leftNode;
	size_t dist;
	T key;
	LeftistNode(T key) : rightNode(NULL), leftNode(NULL), key(key) {}
	LeftistNode(const LeftistNode *b) : rightNode(b->rightNode), leftNode(b->leftNode), 
		key(b->key), dist(b->dist) {}
	~LeftistNode() {
		if (leftNode) {
			delete leftNode;
			leftNode = NULL;
		}
		if (rightNode) {
			delete rightNode;
			right = NULL;
		}
	}
};

template <class T> LeftistNode<T>*  _Merge(LeftistNode<T>* root_1, LeftistNode<T>*  root_2) {
	
	LeftistNode<T>* firstRoot = root_1;
	LeftistNode<T>* secondRoot = root_2;

	if (firstRoot == NULL)
		return secondRoot;
	else if (secondRoot == NULL)
		return firstRoot;

	if (!Less(firstRoot->key, secondRoot->key))
	{
		LeftistNode<T>* temp = firstRoot;
		firstRoot = secondRoot;
		secondRoot = temp;
	}

	firstRoot->rightNode = _Merge(firstRoot->rightNode, secondRoot);

	if (firstRoot->leftNode == NULL) {
		firstRoot->leftNode = firstRoot->rightNode;
		firstRoot->rightNode = NULL;

	}
	else {
		if (firstRoot->leftNode->dist < firstRoot->rightNode->dist) {
			LeftistNode<T> *temp = firstRoot->leftNode;
			firstRoot->leftNode = firstRoot->rightNode;
			firstRoot->rightNode = temp;
		}
		firstRoot->dist = firstRoot->rightNode->dist + 1;
	}
	return firstRoot;
}

template <class T> class CLeftistHeap :public IHeap<T> {
private:
	LeftistNode<T> *head;
	size_t sizeOfHeap;
public:
	CLeftistHeap():head(NULL), sizeOfHeap(0) {}
	CLeftistHeap(T key): head(NULL), sizeOfHeap(1) {
		head = new LeftistNode<T>(key);
	}
	~CLeftistHeap()
	{
		delete head;
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
		LeftistNode<T> *tmp = new LeftistNode<T>(key);
		head = _Merge<T>(head, tmp);
		sizeOfHeap++;
	}
	
	void merge(IHeap<T>* HeapSecond)
	{
		sizeOfHeap += dynamic_cast<CLeftistHeap<T>*> (HeapSecond)->sizeOfHeap;
		head = _Merge(head, dynamic_cast<CLeftistHeap<T>*> (HeapSecond)->head);
	}
};