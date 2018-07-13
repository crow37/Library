#pragma once
#include "Exports.h"

namespace CPU_INFO
{
	class EXPORTS_API CPU
	{
	public:
		/*****************************************
		CPU���� �����ϴ� ������ ���� ��ȯ
		******************************************/
		static int GetThreadCount();

		 /*****************************************
		���� ������ �������� ������ ã���ش�

		efficient : ȿ������
		******************************************/
		static int GetEfficientThreadCount(int p_length);
	};
}

