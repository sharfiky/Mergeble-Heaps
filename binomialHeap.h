#pragma once
#include <iostream>
#include "comparators.h"
#include "IHeap.h"

using namespace std;

const int SIZE = 31;
const int INF = 1 << 30;

template <class T> struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;
	Node() {}
	Node(T Data) {
		data = Data;
		left = 0;
		right = 0;
	}
	Node(const Node<T> &n) {
		data = n.data;
		Node<T> *l = 0, *r = 0;
		if (n.left) l = new Node<T>(*n.left);
		if (n.right) r = new Node<T>(*n.right);
		left = l;
		right = r;
	}
	~Node() {
		if (left) {
			delete left;
			left = 0;
		}
		if (right) {
			delete right;
			right = 0;
		}
	}

};

template <class T> struct CBinomialHeap :public IHeap<T>{
private:
	Node<T>* mas[SIZE];
	int size;
public:
	CBinomialHeap() { memset(mas, 0, sizeof(mas)); size = 0; }
	CBinomialHeap(T Data)
	{
		memset(mas, 0, sizeof(mas));
		size = 1;
		mas[0] = new Node<T>(Data);
	}
	CBinomialHeap(const CBinomialHeap &bq) {

		memset(mas, 0, sizeof(mas));

		size = bq.size;
		for (int i = 0; i<SIZE; i++) {
			if (bq.mas[i]) {
				Node<T>* deepCopy = new Node<T>(*bq.mas[i]);
				mas[i] = deepCopy;
			}
		}
	}
	~CBinomialHeap() {
		for (int i = 0; i<SIZE; ++i) {
			if (mas[i])
				delete mas[i];
		}
	}
	void clear() {
		memset(mas, 0, sizeof(mas)); size = 0;
	}
	bool empty() {
		return size == 0;
	}
	Node<T>* join(Node<T>* f, Node<T> *s) {
		if (Less(f->data, s->data)) { 
			s->right = f->left; f->left = s; return f;
		}
		else {
			f->right = s->left; s->left = f; return s;
		}
	}
	int num(int c, int b, int a) {
		return 4 * c + 2 * b + a;
	}
	void joinBQ(Node<T>* a[], Node<T>* b[]) {
		Node<T>* c = 0;
		for (int i = 0; i<SIZE; i++) {
			switch (num(c != 0, b[i] != 0, a[i] != 0)) {
			case 2: a[i] = b[i]; break;
			case 3: c = join(a[i], b[i]); a[i] = 0; break;
			case 4: a[i] = c; c = 0; break;
			case 5: c = join(a[i], c); a[i] = 0; break;
			case 6:
			case 7: c = join(b[i], c); break;
			}
		}
	}
	void merge(IHeap<T>* HeapSecond) {
		CBinomialHeap<T> *bq = dynamic_cast<CBinomialHeap<T>*> (HeapSecond);
		joinBQ(mas, bq->mas);
		size += bq->size;
		bq->clear();
	}
	void insert(int val) {
		Node<T>* newNode = new Node<T>(val);
		Node<T>* curNode = newNode;
		for (int i = 0; i<SIZE; i++) {
			if (mas[i] == NULL) {
				mas[i] = curNode;
				break;
			}
			else {
				curNode = join(curNode, mas[i]);
				mas[i] = NULL;
			}
		}
		size++;
	}
	T extractMin() {
		T res = INF;
		size_t resPos = -1;
		for (int i = 0; i < SIZE; i++) {
			if (mas[i] && Less(mas[i]->data, res)) {

				res = mas[i]->data;
				resPos = i;
			}
		}
		Node<T>** tmp = new Node<T>*[SIZE];
		memset(tmp, 0, sizeof(tmp)*SIZE);
		Node<T>* cur = mas[resPos]->left;
		for (int i = resPos - 1; i >= 0; i--) {
			tmp[i] = new Node<T>(*cur);
			cur = cur->right;
			tmp[i]->right = 0;
		}
		delete mas[resPos];
		mas[resPos] = 0;

		joinBQ(mas, tmp);
		delete tmp;
		size--;
		return res;
	}
};