#pragma once
#include "Exports.h"
#include "CPU.h"

using namespace CPU_INFO;

//
//현재 문제점 :	스레드의 갯수 만큼 행렬 안의 각각의 성분의 계산 값이 대입된다. / 그 외 전부다...바꿔
//				
//

namespace MathFuncs
{
	mutex g_mt;

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
		int l_ThreadCount = CPU::GetThreadCount();

		//중요
		//l_Garbage / l_WorkLoad에 관해서 재확인
		//int l_Garbage = l_MatrixLength % l_ThreadCount;
		int l_Garbage = 0;
		int l_WorkLoad = (int)(l_MatrixLength / l_ThreadCount);

		//스레드 갯수를 길이 만큼 맞추는 함수 재수정
		l_ThreadCount = CPU::GetEfficientThreadCount(l_MatrixLength);

		A* l_MatrixMul = new A[l_MatrixLength];
		//할당된 메모리의 초기화하는 함수...(확인을 위해서 작성해봤음)
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
			//바뀐 알고리즘
			//
			//스레드 하나에 행렬곱의 성분들을 담아내는 대입....
			l_ThreadList[l_idxThread] = thread(M_Thread_Mul<A, B>, l_MatrixMul, p_ItemA, p_ItemB,
				p_lenRowA, p_lenColA, p_lenRowB, p_lenColB, l_CurRow, 2);

			//중요
			//CurRow에 대해서도 재확인
			//l_CurRow += 2 + 1;
			//행렬 그림 그려보면 알게됨...ex) 0, 1, 2, 3
			l_CurRow += 2;

			//현재 안들어옴 정리해야됨
			//현재 Garbage없이 일단 스레드에 행렬곱의 값이 대입이 되는지 확인하기 위해 작성함
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
			cout << "일치 하지 않음" << endl;
			return;
		}
		//스레드의 중복 방지...(현재는 스레드가 하나만 생성되서 대입하기에 상관없다)
		lock_guard<mutex> l_lg(g_mt);
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

				//thread 행렬곱의 값을 저장...
				p_Catch[(p_lenColB * row) + col] = l_temp;
				cout << p_Catch[(p_lenColB * row) + col] << ": 얻어낸 점수"<< endl;
			}
		}
	}
#pragma endregion MT_Mul

#pragma endregion Matrix_Formula
}
