#pragma once

#include <vector>
#include "IHeap.h"
#include "comparators.h"
#include "protoNode.h"

template <class T> class LeftistNode  {
public:
	LeftistNode *rightNode;
	LeftistNode *leftNode;
	size_t dist;
	T key;
	LeftistNode(T key) : rightNode(NULL), leftNode(NULL), key(key) {}
	LeftistNode(const LeftistNode *b) : rightNode(b->rightNode), leftNode(b->leftNode), 
		key(b->key), dist(b->dist) {}
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
public:
	CLeftistHeap():head(NULL) {}
	T getMin()
	{
		return head->key;
	}
	void extractMin()
	{
		head = _Merge<T>( head->rightNode,  head->leftNode);
	}
	void insert(T key)
	{
		LeftistNode<T> *tmp = new LeftistNode<T>(key);
		head = _Merge<T>(head, tmp);
	}
};