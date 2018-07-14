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

	// �Ϲ� ������ ī���Ͷ� ȿ������ ī���Ͷ� �켱���� ���ϱ�...
	// ���࿡ ȿ���� �켱������ �� ���ٸ� �׳� �Ϲ� �����带 ����� �ʿ䰡 ����.
	// �Ϲ� �����带 ��ߵǴ� ��Ȳ�̶� ȿ�� ������ ��Ȳ�̶� ��������...........
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