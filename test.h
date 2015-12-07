#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "IHeap.h"
#include "skew.h"
#include "leftist.h"
#include "binomialHeap.h"
#include "interface.h"
#include <ctime>


std::ofstream result("result.txt");

typedef int timeType;

timeType getTime()
{
	return clock() ;
}

template< class Heap> bool AddDoing(int a, Interface<int, Heap> &H)
{
	H.AddHeap(a);
	return 0;
}

template< class Heap> bool InsertDoing(int a, int b, Interface<int, Heap> &H)
{
	if (H.numberOfHeaps() == 0)
		return false;
	H.Insert(a % H.numberOfHeaps(), b);
	return true;
}

template< class Heap> pair <bool, int> ExtractMinDoing(int a, Interface<int, Heap> &H)
{
	if (H.numberOfHeaps() == 0)
		return make_pair(0, -1);
	int num = a % H.numberOfHeaps();
	if (H.Empty(num))
		return make_pair(0, num);
	int tmp = H.ExtractMin(num);
	return make_pair(1, tmp);
}

template< class Heap> bool MeldDoing(int a, int b, Interface<int, Heap> &H)
{
	if (H.numberOfHeaps() == 0)
		return false;
	H.Meld(a % H.numberOfHeaps(), b % H.numberOfHeaps());
	return true;
}



void testGen(int N)
{
	std::ofstream testFile("test.txt");

	for (int i = 0; i < N; ++i)
	{
		int number = rand() % 4;
		if (number == 0)
		{
			int a = rand();
			testFile << "AddHeap( " << a << ");\n";
		}
		else if (number == 1)
		{
			int a = rand(), b = rand();
			testFile << "Insert( " << a << ", " << b << ");\n";
		}
		else if (number == 2)
		{
			int a = rand();
			testFile << "ExtractMin( " << a << ");\n";
		}
		else
		{
			int a = rand(), b = rand();
			testFile << "Meld( " << a << ", " << b << ");\n";
		}
	}
}

bool checkMeld(std::string &a)
{
	return a[0] == 'M';
}
bool checkInsert(std::string &a)
{
	return a[0] == 'I';
}
bool checkExtractMin(std::string &a)
{
	return a[0] == 'E';
}
bool checkAdd(std::string &a)
{
	return a[0] == 'A';
}

template<class T> bool checkthree(T &a, T &b, T &c)
{
	return a == b && b == c;
}

template <class Heap> void checkOneHeap(int N, vector <pair<bool, int> > &vect, timeType &time)
{
	timeType t = getTime();
	std::freopen("test.txt", "r", stdin);
	Interface<int, Heap> H;
	for (int i = 0; i < N; ++i)
	{
		std::string s;
		std::cin >> s;
		if (checkAdd(s))
		{
			int a;
			scanf("%d", &a);
			AddDoing(a, H);
			vect.push_back(make_pair(0, 0));
		}
		else if (checkMeld(s))
		{
			int a, b;
			scanf("%d,%d", &a, &b);
			vect.push_back(make_pair(0, MeldDoing(a, b, H)));
		}
		else if (checkInsert(s))
		{
			int a, b;
			scanf("%d,%d", &a, &b);
			vect.push_back(make_pair(0, InsertDoing(a, b, H)));
			
		}
		else if (checkExtractMin(s))
		{
			int a;
			scanf("%d", &a);
			vect.push_back(ExtractMinDoing(a, H));
			
		}
		std::cin >> s;
	}
	time += (getTime() - t);
}

void checker(int N)
{
	timeType skewTime(0), binTime(0), lefTime(0);
	vector <pair <bool, int> > a, b, c;
	checkOneHeap<CSkewHeap<int>> (N, a, skewTime);
	checkOneHeap<CLeftistHeap<int>> (N, b, lefTime);
	checkOneHeap<CBinomialHeap<int>> (N, c, binTime);
	for (int i = 0; i < N; ++i)
		if (!checkthree(a[i], b[i], c[i]))
		{
			result << "error " << i << "\n";
			return;
		}

	result << "Everything is awesome\n";
	result << "WorkTime of SkewHeap is " << skewTime  <<"\n";
	result << "WorkTime of LeftistHeap is " << lefTime << "\n";
	result << "WorkTime of BinomialHeap is " << binTime << "\n\n";

}

void composite(int N)
{
	testGen(N);
	checker(N);
}