#pragma once
#include "Exports.h"

namespace CPU_INFO
{
	class EXPORTS_API CPU
	{
	public:
		/*****************************************
		CPU에서 지원하는 스레드 개수 반환
		******************************************/
		static int GetThreadCount();

		 /*****************************************
		가장 적절한 스레드의 개수를 찾아준다

		efficient : 효율적인
		******************************************/
		static int GetEfficientThreadCount(int p_length);
	};
}

