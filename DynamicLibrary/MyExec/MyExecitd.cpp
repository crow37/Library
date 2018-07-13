
#include <iostream>
#include <Windows.h>
#include "MathFuncsDll.h"

using namespace std;
using namespace MathFuncs;

int main()
{
	int* array1 = new int[8]{ 1, 2, 3, 4, 5, 6, 7, 8};
	int* array2 = new int[4]{ 4, 4, 4, 4 };

	int* arrayMatrix = MyMathFuncs::Matrix_Mul<int, int>(array1, array2, 4, 2, 2, 2);

	for (int i = 0; i < 8; ++i)
	{
		cout << arrayMatrix[i] << endl;
	}

	return 0;
}