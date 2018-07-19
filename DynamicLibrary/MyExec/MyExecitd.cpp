
#include <iostream>
#include <Windows.h>
#include "MathFuncsDll.h"

using namespace std;
using namespace MathFuncs;

int main()
{
	int* array1 = new int[64]{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,2, 2, 2, 2, 2, 2};
	int* array2 = new int[64]{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1};

	clock_t begin;
	begin = clock();

	int* array3 = MyMathFuncs::Matrix_Mul<int, int>(array1, array2, 32, 2, 2, 32);

	cout << "수행시간 : " << ((clock() - begin) / 1000.0f) << endl;
	
	delete(array1);
	delete(array2);
	delete(array3);

	return 0;
}