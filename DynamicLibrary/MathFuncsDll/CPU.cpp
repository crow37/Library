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

	if (p_length < l_ThreadCount)
	{
		l_ThreadCount = p_length;
	}
	else if (p_length < l_EfficientCount)
	{
		l_ThreadCount = p_length;
	}

	return l_EfficientCount;
}