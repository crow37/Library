
#include <iostream>
#include <Windows.h>
#include "MathFuncsDll.h"

using namespace std;
using namespace MathFuncs;

//���ο��� �����带 �����ϴ� �Լ��� ȣ���ؼ� �� ������ŭ
//Matrix_Mul �ϳ��� �����Ѵ�.
//�׷��� ������� ����� ���� ���� ��������.
int main()
{
	//int* array1 = new int[4]{ 1, 2, 3, 4 };
	//int* array2 = new int[4]{ 4, 4, 4, 4 };
	int array1[4] = { 1, 2, 3, 4 };
	int array2[4] = { 4,4,4,4 };

	int* arrayMatrix = MyMathFuncs::Matrix_Mul<int, int>(array1, array2, 2, 2, 2, 2);

	//������ ���� �Լ� : ����� ���� ��ŭ ������ �� �ֵ��� �����...
	//
	//��ĵ��� ������ �ٸ� ����� �Լ� : �� ��ĵ��� �� �ε��� �迭�� ���� ���ѳ��� �� ���� 
	//������ �迭 ��ŭ ���� for���� ������ ������鳢�� ���� ����ϵ��� �����Ѵ�...
	//
	//������[i] = ����� ��[i]...�˰��� ex)
	//���� �帧�� ����.....
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