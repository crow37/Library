#include "stdafx.h"
#include "CPU.h"

using namespace CPU_INFO;

int CPU::GetThreadCount()
{
	return thread::hardware_concurrency();
}

int CPU::GetEfficientThreadCount(int p_length)
{
	int l_ThreadCount = GetThreadCount();

	if (p_length < l_ThreadCount)
	{
		l_ThreadCount = p_length;
	}
	return l_ThreadCount;
}