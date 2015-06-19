#ifndef _HR_MEMORYSTACK_H_
#define _HR_MEMORYSTACK_H_

#include <memory>
#include "../../HrCommon/HrCCBase/HrBasicType.h"

namespace HrPool
{
	class CHrMemoryStackToken;
	class CHrMemoryStack
	{
	public:
		CHrMemoryStack();
		~CHrMemoryStack();

	public:
		/**
		*	@Comment: ������Դ [3/6/2015 By Hr]
		*	@Param:   nSize:�����ڴ�Ĵ�С
		*/
		void*				Mallock(uint64 nSize);
		/**
		*	@Comment: �ͷ���Դ [3/6/2015 By Hr]
		*/
		bool                Free(void* pMemory);

		/**
		*	@Comment: ��ӡ���ٵĶ�����Ϣ [3/8/2015 By Hr]
		*/
		void                PrintStack();
		/**
		*	@Comment: ��ӡ���ٵ��ڴ���Ϣ [3/8/2015 By Hr]
		*/
		void                PrintInfo();
	private:
		CHrMemoryStackToken* m_pStackTokenHead;
		//�ڴ������ַ
		uint64               m_nMaxMemoryAddress;
		//�����˶����ڴ��
		uint                m_nAllBlockCount;
		//һ���ж����ڴ���ʹ��
		uint                m_nMemoryUsed;
		bool                m_bCloseFlag;
	};
}



#endif // !_HR_MEMORYSTACK_H_



