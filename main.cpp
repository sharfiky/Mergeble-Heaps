#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <fstream>
#include "IHeap.h"
#include <vector>
#include "skew.h"
#include "leftist.h"
#include "binomialHeap.h"
#include "interface.h"
#include "test.h"



int main()
{
	for (int i = 10; i <= 1000 * 1000; i *= 10)
		composite(i);
	
	system("pause");
	return 0;
}

