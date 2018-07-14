
#include <iostream>
#include <Windows.h>
#include "MathFuncsDll.h"

using namespace std;
using namespace MathFuncs;

//메인에서 스레드를 생성하는 함수를 호출해서 그 갯수만큼
//Matrix_Mul 하나씩 대입한다.
//그러면 스레드당 행렬의 곱의 값이 정해진다.
int main()
{
	//int* array1 = new int[4]{ 1, 2, 3, 4 };
	//int* array2 = new int[4]{ 4, 4, 4, 4 };
	int array1[4] = { 1, 2, 3, 4 };
	int array2[4] = { 4,4,4,4 };

	int* arrayMatrix = MyMathFuncs::Matrix_Mul<int, int>(array1, array2, 2, 2, 2, 2);

	//스레드 생성 함수 : 행렬의 갯수 만큼 생성할 수 있도록 만들기...
	//
	//행렬들의 성분이 다를 경우의 함수 : 그 행렬들을 각 인덱스 배열에 대입 시켜놓고 그 값을 
	//스레드 배열 만큼 같이 for문을 돌려서 스레드들끼리 각자 계산하도록 유도한다...
	//
	//스레드[i] = 행렬의 곱[i]...알고리즘 ex)
	//대충 흐름만 만듬.....
	/*for (int i = 0; i < Matrix_Mul.count; ++i)
	{
		l_threadCount[i] = newThreadFunc(i);
		arrayMatrix[i] = MyMathFuncs::Matrix_Mul<int, int>(array1, array2, 2, 2, 2, 2);
		l_threadCount[i] = arrayMatrix[i];
	}*/

	for (int i = 0; i < 4; ++i)
	{
		cout << arrayMatrix[i] << endl;
	}

	return 0;
}