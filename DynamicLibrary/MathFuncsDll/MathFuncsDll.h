#pragma once
#include "Exports.h"
#include "CPU.h"

using namespace CPU_INFO;

namespace MathFuncs
{
	mutex g_mutex;

	class EXPORTS_API MyMathFuncs
	{
	public:
		/***************************************
		행렬 관련 연산 :  https://ko.wikipedia.org/wiki/%ED%96%89%EB%A0%AC

		Row          = 세로 길이 : 행
		Col (Column) = 가로 길이 : 열
		***************************************/

		/**************************************
					행렬의 공식
		**************************************/
		template<typename A, typename B>
		static A* Matrix_Sum(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Matrix_Sub(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Matrix_Mul(A* p_ItemA, B* p_ItemB,
			int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB);

		/**************************************
		행렬 스레드 의 공식 M_Thread = Matrix Thread
		**************************************/
		template<typename A, typename B>
		static void M_Thread_Mul(A* p_Catch, A* p_ItemA, B* p_ItemB,
			int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB, 
			int p_StartRowIdx, int p_ThreadLen);

	};

#pragma region Matrix_Formula
	/**************************************
				행렬의 공식
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
			cout << "일치 하지 않음" << endl;
			return NULL;
		}

		int l_MatrixLength = p_lenRowA * p_lenColB;
		int l_ThreadCount = CPU::GetEfficientThreadCount(p_lenRowA);

		A* l_MatrixMul = new A[l_MatrixLength];
		thread* l_ThreadList = new thread[l_ThreadCount];

		for (int i = 0; i < l_ThreadCount; ++i)
		{
			l_ThreadList[i] = thread(M_Thread_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
				p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, i, l_ThreadCount);
		}

		for (int i = 0; i < l_ThreadCount; ++i)
		{
			l_ThreadList[i].join();
		}

		return l_MatrixMul;
	}
#pragma endregion Matrix_Mul

#pragma region M_Thread_Mul
	template<typename A, typename B>
	void MyMathFuncs::M_Thread_Mul(A* p_Result, A* p_ItemA, B* p_ItemB,
		int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB,
		int p_StartRowIdx, int p_ThreadLen)
	{
		if (p_lenColA != p_lenRowB)
		{
			cout << "일치 하지 않음" << endl;
			return;
		}

		for (int i = 0; i < 100000; ++i)
		{
			for (int i = 0; i < 10000000; ++i)
			{
				for (int row = p_StartRowIdx; row < p_lenRowA; row += p_ThreadLen)
				{
					for (int col = 0; col < p_lenColB; ++col)
					{
						A l_temp = 0;
						for (int idx = 0; idx < p_lenColA; ++idx)
						{
							l_temp += p_ItemA[(p_lenColA * row) + idx] * p_ItemB[(p_lenColB * idx) + col];
						}

						p_Result[(p_lenColB * row) + col] = l_temp;
					}
				}
			}
		}				
	}
#pragma endregion MT_Mul

#pragma endregion Matrix_Formula
}
