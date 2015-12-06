#include <iostream>
#include <fstream>
#include "IHeap.h"
#include <vector>
#include "skew.h"
#include "leftist.h"
#include "binomialHeap.h"
#include "interface.h"

std::ofstream testFile("test.txt");
std::ofstream answerFile("answer.txt");
template< class Heap> void firstDoing(int a, int b, Interface<int, Heap> &H)
{
	if (H.numberOfHeaps() == 0)
	{
		answerFile << "array is empty\n";
		return ;
	}
	H.Insert(a % H.numberOfHeaps(), b);
}

template< class Heap> void secondDoing(int a, Interface<int, Heap> &H)
{
	if (H.numberOfHeaps() == 0)
	{
		answerFile << "array is empty\n";
		return;
	}
	int num = a % H.numberOfHeaps();
	if (H.Empty(num))
	{
		answerFile << "heap N " << num << "is empty\n";
		return;
	}
	answerFile << H.ExtractMin(num) << "\n";
}

template< class Heap> void thirdDoing(int a, int b,  Interface<int, Heap> &H)
{
	if (H.numberOfHeaps() == 0)
	{
		answerFile << "array is empty\n";
		return;
	}
	H.Meld(a % H.numberOfHeaps(), b % H.numberOfHeaps());
}



void step(Interface<int, CBinomialHeap<int>> &bin, Interface<int, CLeftistHeap<int>> &lef, 
	Interface<int, CSkewHeap<int>> &skew)
{
	int number = rand() % 4;
	if (number == 0)
	{
		int a = rand();
		testFile << "AddHeap (" << a << ");\n";
		bin.AddHeap(a);
		lef.AddHeap(a);
		skew.AddHeap(a);
		answerFile << "\n\nlasts test 0 \n\n";
	}
	else if (number == 1)
	{
		int a = rand(), b = rand();
		testFile << "Insert(" << a << ", " << b << ");\n";
		firstDoing(a, b, bin);
		firstDoing(a, b, lef);
		firstDoing(a, b, skew);
		answerFile << "\n\nlasts test 1 \n\n";
	}
	else if (number == 2)
	{
		int a = rand();
		testFile << "ExtractMin(" << a << ");\n";
		secondDoing(a, bin);
		secondDoing(a, lef);
		secondDoing(a, skew);
		answerFile << "\n\nlasts test 2 \n\n";
	}
	else
	{
		int a = rand(), b = rand();
		testFile << "meld(" << a << ", " << b << ");\n";
		thirdDoing(a, b, bin);
		thirdDoing(a, b, lef);
		thirdDoing(a, b, skew);
		answerFile << "\n\nlasts test 3 \n\n";
	}
}

int main()
{
	Interface<int, CBinomialHeap<int>> bin;
	Interface<int, CLeftistHeap<int>> lef;
	Interface<int, CSkewHeap<int>> skew;
	for (int i = 0; i < 10000; ++i)
		step(bin, lef, skew);

	system("pause");
	return 0;
}