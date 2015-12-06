#pragma once

#include <vector>
#include "IHeap.h"
#include "comparators.h"
#include "protoNode.h"

template <class T> class SkewNode : public ProtoNode<T> {
public:
	SkewNode() {}
	SkewNode(T key): ProtoNode(key){}
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
	if (Less(firstRoot->key, secondRoot->key))
	{
		SkewNode<T>* tempHeap = firstRoot->rightNode;
		firstRoot->rightNode = firstRoot->leftNode;
		firstRoot->leftNode = _Merge(secondRoot, tempHeap);
		return firstRoot;
	}
	else
		return _Merge(secondRoot, firstRoot);
}

template <class T> class CSkewHeap :public IHeap<T>{
private:
	SkewNode<T> *head;
public:
	CSkewHeap():head(NULL){}
	T getMin()
	{
		return head->key;
	}
	void extractMin()
	{
		head = _Merge(head->rightNode, head->leftNode);
	}
	void insert(T key)
	{
		SkewNode<T> *tmp = new SkewNode<T>(key);
		head = _Merge(head, tmp);
	}
};