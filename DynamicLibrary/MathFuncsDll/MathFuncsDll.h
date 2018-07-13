#pragma once
#include "Exports.h"
#include "CPU.h"

using namespace CPU_INFO;

namespace MathFuncs
{
	mutex mt;

	class EXPORTS_API MyMathFuncs
	{
	public:
		/***************************************
		행렬 관련 연산 :  https://ko.wikipedia.org/wiki/%ED%96%89%EB%A0%AC

		Row          = 세로 길이 : 행
		Col (Column) = 가로 길이 : 열
		***************************************/

		/**************************************
					배열의 공식
		**************************************/
		template<typename A, typename B>
		static A* Array_Sum(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Array_Sub(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Array_Mul(A* p_ItemA, B* p_ItemB, int p_length);

		/**************************************
					행열의 공식
		**************************************/
		template<typename A, typename B>
		static A* Matrix_Sum(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Matrix_Sub(A* p_ItemA, B* p_ItemB, int p_length);
		template<typename A, typename B>
		static A* Matrix_Mul(A* p_ItemA, B* p_ItemB,
			int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB);

		/**************************************
		행열 스레드 의 공식 MT = Matrix Thread
		**************************************/
		template<typename A, typename B>
		static void MT_Mul(A* p_Catch, A* p_ItemA, B* p_ItemB,
			int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB, 
			int p_StartRowIdx, int p_IncludeCount);

	};

#pragma region Array_Formula
	/**************************************
				배열의 공식
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
				행열의 공식
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

		A* l_MatrixMul = new A[p_lenRowA * p_lenColB];

		for (int row = 0; row < p_lenRowA; ++row)
		{
			for (int col = 0; col < p_lenColB; ++col)
			{
				A l_temp = 0;
				for (int idx = 0; idx < p_lenColA; ++idx)
				{
					//가로의 idx 만큼 길이 얻기, 세로의 col 만큼 길이 얻기
					l_temp += p_ItemA[(p_lenColA * row) + idx] * p_ItemB[(p_lenColB * idx) + col];
				}

				//행렬의 길이 위치 저장
				l_MatrixMul[(p_lenColB * row) + col] = l_temp;
			}
		}

		/*int l_MatrixLength = p_lenRowA * p_lenColB;
		int l_ThreadCount = CPU::GetThreadCount();

		int l_Garbage = l_MatrixLength % l_ThreadCount;
		int l_WorkLoad = (int)(l_MatrixLength / l_ThreadCount);
		l_ThreadCount = CPU::GetEfficientThreadCount(l_MatrixLength);

		A* l_MatrixMul = new A[l_MatrixLength];

		thread* l_ThreadList = new thread[l_ThreadCount];

		int l_CurRow = 0;
		for (int i = 0; i < l_ThreadCount; ++i)
		{
			if (l_Garbage > 0)
			{
				l_ThreadList[i] = thread(MT_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
					p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, l_CurRow, l_WorkLoad + 1);

				l_CurRow += l_WorkLoad + 1;
				--l_Garbage;
			}
			else
			{
				l_ThreadList[i] = thread(MT_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
					p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, l_CurRow, l_WorkLoad);

				l_CurRow += l_WorkLoad + 1;
				--l_Garbage;
			}
		}

		for (int i = 0; i < l_ThreadCount; ++i)
		{
			l_ThreadList[i].join();
		}*/

		return l_MatrixMul;
	}
#pragma endregion Matrix_Mul

#pragma region MT_Mul
	template<typename A, typename B>
	void MyMathFuncs::MT_Mul(A* p_Catch, A* p_ItemA, B* p_ItemB,
		int p_lenRowA, int p_lenColA, int p_lenRowB, int p_lenColB,
		int p_StartRowIdx, int p_IncludeCount)
	{
		if (p_lenColA != p_lenRowB)
		{
			cout << "일치 하지 않음" << endl;
			return;
		}

		for (int row = p_StartRowIdx; row < p_StartRowIdx + p_IncludeCount; ++row)
		{
			for (int col = 0; col < p_lenColB; ++col)
			{
				A l_temp = 0;
				for (int idx = 0; idx < p_lenColA; ++idx)
				{
					//p_ItemA[(p_lenColA * row) + idx] 가로 idx만큼의 길이 얻기
					//p_ItemB[(p_lenColB * idx) + col] 세로 col만큼의 길이 얻기
					l_temp += p_ItemA[(p_lenColA * row) + idx] * p_ItemB[(p_lenColB * idx) + col];
				}

				//thread 행렬의 길이 위치 저장
				mt.lock();
				p_Catch[(p_lenColB * row) + col] = l_temp;
				mt.unlock();
			}
		}
	}
#pragma endregion MT_Mul

#pragma endregion Matrix_Formula
}
