#pragma once
#include "Exports.h"
#include "CPU.h"

using namespace CPU_INFO;

//
//���� ������ :	�������� ���� ��ŭ ��� ���� ������ ������ ��� ���� ���Եȴ�. / �� �� ���δ�...�ٲ�
//				
//

namespace MathFuncs
{
	mutex g_mt;

	class EXPORTS_API MyMathFuncs
	{
	public:
		/***************************************
		��� ���� ���� :  https://ko.wikipedia.org/wiki/%ED%96%89%EB%A0%AC

		Row          = ���� ���� : ��
		Col (Column) = ���� ���� : ��
		***************************************/

		/**************************************
					�迭�� ����
		**************************************/
		template<typename A, typename B>
		static A* Array_Sum(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Array_Sub(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Array_Mul(A* p_ItemA, B* p_ItemB, int p_length);

		/**************************************
					����� ����
		**************************************/
		template<typename A, typename B>
		static A* Matrix_Sum(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Matrix_Sub(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Matrix_Mul(A* p_ItemA, B* p_ItemB,
			int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB);

		/**************************************
		��� ������ �� ���� M_Thread = Matrix Thread
		**************************************/
		template<typename A, typename B>
		static void M_Thread_Mul(A* p_Catch, A* p_ItemA, B* p_ItemB,
			int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB, 
			int p_StartRowIdx, int p_IncludeCount);

	};

#pragma region Array_Formula
	/**************************************
				�迭�� ����
	**************************************/
#pragma region Array_Sum

	template<typename A, typename B>
	A* MyMathFuncs::Array_Sum(A* p_ItemA, B* p_ItemB, int p_length)
	{
		A* l_arraySum = new A[p_length];

		for (int i = 0; i < p_length; ++i)
		{
			l_arraySum[i] = p_ItemA[i] + p_ItemB[i];
		}

		return l_arraySum;
	}

#pragma endregion Array_Sum

#pragma region Array_Sub

	template<typename A, typename B>
	A* MyMathFuncs::Array_Sub(A* p_ItemA, B* p_ItemB,
		int p_length)
	{
		A* l_arraySub = new A[p_length];

		for (int i = 0; i < p_length; ++i)
		{
			l_arraySub[i] = p_ItemA[i] - p_ItemB[i];
		}

		return l_arraySub;
	}

#pragma endregion Array_Sub

#pragma region Array_Mul

	template<typename A, typename B>
	A* MyMathFuncs::Array_Mul(A* p_ItemA, B* p_ItemB,
		int p_length)
	{
		A* l_arrayMul = new A[p_length];

		for (int i = 0; i < p_length; ++i)
		{
			l_arrayMul[i] = p_ItemA[i] * p_ItemB[i];
		}

		return l_arrayMul;
	}

#pragma endregion Array_Mul
#pragma endregion Array_Formula

#pragma region Matrix_Formula
	/**************************************
				����� ����
	**************************************/
#pragma region Matrix_Sum
	template<typename A, typename B>
	A* MyMathFuncs::Matrix_Sum(A* p_ItemA, B* p_ItemB, int p_length)
	{
		A* l_SumMatrix = new A[p_length];

		for (int i = 0; i < p_length; ++i)
		{
			l_SumMatrix[i] = p_ItemA[i] + p_ItemB[i];
		}

		return l_SumMatrix;
	}
#pragma endregion Matrix_Sum

#pragma region Matrix_Sub
	template<typename A, typename B>
	A* MyMathFuncs::Matrix_Sub(A* p_ItemA, B* p_ItemB, int p_length)
	{
		A* l_SubMatrix = new A[p_length];

		for (int i = 0; i < p_length; ++i)
		{
			l_SubMatrix[i] = p_ItemA[i] + p_ItemB[i];
		}

		return l_SubMatrix;
	}
#pragma endregion Matrix_Sub

#pragma region Matrix_Mul
	template<typename A, typename B>
	A* MyMathFuncs::Matrix_Mul(A* p_ItemA, B* p_ItemB,
		int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB)
	{
		if (p_lenColA != p_lenRowB)
		{
			cout << "��ġ ���� ����" << endl;
			return NULL;
		}

		int l_MatrixLength = p_lenRowA * p_lenColB;
		int l_ThreadCount = CPU::GetThreadCount();

		//�߿�
		//l_Garbage / l_WorkLoad�� ���ؼ� ��Ȯ��
		//int l_Garbage = l_MatrixLength % l_ThreadCount;
		int l_Garbage = 0;
		int l_WorkLoad = (int)(l_MatrixLength / l_ThreadCount);

		//������ ������ ���� ��ŭ ���ߴ� �Լ� �����
		l_ThreadCount = CPU::GetEfficientThreadCount(l_MatrixLength);

		A* l_MatrixMul = new A[l_MatrixLength];
		//�Ҵ�� �޸��� �ʱ�ȭ�ϴ� �Լ�...(Ȯ���� ���ؼ� �ۼ��غ���)
		memset(l_MatrixMul, 0, sizeof(l_MatrixMul));
		thread* l_ThreadList = new thread[l_ThreadCount];

		int l_CurRow = 0;
		int l_idxThread = 0;
		//for (int i = 0; i < l_ThreadCount; ++i)
		{
			//if (l_Garbage > 0)
			//{
			//	l_ThreadList[i] = thread(MT_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
			//		p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, l_CurRow, l_WorkLoad + 1);

			//	l_CurRow += l_WorkLoad + 1;
			//	--l_Garbage;
			//}
			//else
			//{
			//	l_ThreadList[i] = thread(MT_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
			//		p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, l_CurRow, l_WorkLoad);

			//	l_CurRow += l_WorkLoad + 1;
			//	--l_Garbage;
			//}

			//
			//�ٲ� �˰���
			//
			//������ �ϳ��� ��İ��� ���е��� ��Ƴ��� ����....
			l_ThreadList[l_idxThread] = thread(M_Thread_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
				p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, l_CurRow, 2);

			//�߿�
			//CurRow�� ���ؼ��� ��Ȯ��
			//l_CurRow += 2 + 1;
			//��� �׸� �׷����� �˰Ե�...ex) 0, 1, 2, 3
			l_CurRow += 2;

			//���� �ȵ��� �����ؾߵ�
			//���� Garbage���� �ϴ� �����忡 ��İ��� ���� ������ �Ǵ��� Ȯ���ϱ� ���� �ۼ���
			if (l_Garbage > 0)
			{
				l_ThreadList[l_idxThread] = thread(M_Thread_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
					p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, l_CurRow, l_WorkLoad + 1);

				l_CurRow += l_WorkLoad + 1;
				--l_Garbage;
			}

			l_ThreadList[l_idxThread].join();
		}

		return l_MatrixMul;
	}
#pragma endregion Matrix_Mul

#pragma region M_Thread_Mul
	template<typename A, typename B>
	void MyMathFuncs::M_Thread_Mul(A* p_Catch, A* p_ItemA, B* p_ItemB,
		int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB,
		int p_StartRowIdx, int p_IncludeCount)
	{
		if (p_lenColA != p_lenRowB)
		{
			cout << "��ġ ���� ����" << endl;
			return;
		}
		//�������� �ߺ� ����...(����� �����尡 �ϳ��� �����Ǽ� �����ϱ⿡ �������)
		lock_guard<mutex> l_lg(g_mt);
		for (int row = p_StartRowIdx; row < p_StartRowIdx + p_IncludeCount; ++row)
		{
			for (int col = 0; col < p_lenColB; ++col)
			{
				A l_temp = 0;
				for (int idx = 0; idx < p_lenColA; ++idx)
				{
					//p_ItemA[(p_lenColA * row) + idx] ���� idx��ŭ�� ���� ���
					//p_ItemB[(p_lenColB * idx) + col] ���� col��ŭ�� ���� ���
					l_temp += p_ItemA[(p_lenColA * row) + idx] * p_ItemB[(p_lenColB * idx) + col];
				}

				//thread ��İ��� ���� ����...
				p_Catch[(p_lenColB * row) + col] = l_temp;
				cout << p_Catch[(p_lenColB * row) + col] << ": �� ����"<< endl;
			}
		}
	}
#pragma endregion MT_Mul

#pragma endregion Matrix_Formula
}
