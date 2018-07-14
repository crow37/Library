#pragma once
#include "stdafx.h"
#include "CPU.h"

using namespace CPU_INFO;

int CPU::GetThreadCount()
{
	return thread::hardware_concurrency();
}

int CPU::GetEfficientThreadCount(int p_length)
{
	int l_ThreadCount = thread::hardware_concurrency();
	int l_EfficientCount = l_ThreadCount * 2;
	int best = p_length;

	// 일반 스레드 카운터랑 효과적인 카운터랑 우선순위 정하기...
	// 만약에 효율이 우선순위가 더 높다면 그냥 일반 스레드를 사용할 필요가 없다.
	// 일반 스레드를 써야되는 상황이랑 효율 스레드 상황이랑 나누던가...........
	//if (p_length < l_ThreadCount)
	//{
	//	l_ThreadCount = p_length;
	//}
	//else if (p_length < l_EfficientCount)
	//{
	//	l_ThreadCount = p_length;
	//}

	if (best > l_EfficientCount) best = l_EfficientCount;
	if (best > l_ThreadCount) best = l_ThreadCount;

	//return l_EfficientCount;
	return best;
}