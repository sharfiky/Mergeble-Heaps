#include <iostream>
#include "IHeap.h"
#include <vector>
#include "skew.h"
#include "leftist.h"



int main()
{
	CLeftistHeap<int> b;
	for (int i = 0; i < 10; ++i)
		b.insert(rand());
	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", b.getMin());
		b.extractMin();
	}
	system("pause");
	return 0;
}