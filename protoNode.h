#pragma once

template <class T> class ProtoNode {
public:
	ProtoNode *rightNode;
	ProtoNode *leftNode;
	T key;
	ProtoNode(T key) : rightNode(NULL), leftNode(NULL), key(key) {}
	ProtoNode(const ProtoNode *b) : rightNode(b->rightNode), leftNode(b->leftNode),
		key(key) {}
};
