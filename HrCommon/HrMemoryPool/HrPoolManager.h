#ifndef _HR_POOLMANAGER_H_
#define _HR_POOLMANAGER_H_

#include "../../HrCommon/HrCCBase/HrBasicType.h"

#include <list>

namespace HrPool
{
	class CHrMemoryStack;
	class CHrMemoryRegister;
	class CHrPoolListener;
	class CHrPoolManager
	{
	public:
		CHrPoolManager(bool bOpenRegister = false);
		~CHrPoolManager();

	public:

		/**
		*	@Brief: 分配内存 [3/5/2015 By Hr]
		*/
		void*		Malloc(uint64 nSize, char* szInfo);
		/**
		*	@Brief: 释放内存 [3/5/2015 By Hr]
		*/
		void        Free(void* pMemory);


		void        PrintTree();
		void        PrintInfo();

		void        Release();

		void        RegisterPoolListener(CHrPoolListener* pListener)
		{
			if (pListener != nullptr)
			{
				m_lisPoolListener.push_back(pListener);
			}
		}

		void        UnRegistePoolListener(CHrPoolListener* pListener)
		{
			for (auto itItem = m_lisPoolListener.begin(); itItem != m_lisPoolListener.end(); ++itItem)
			{
				if (*itItem == pListener)
				{
					m_lisPoolListener.erase(itItem);
					break;
				}
			}
		}

	private:
		void        RegisterMemoryInfo(void* pMemory, char* szInfo);
		void        UnRegisteMemoryInfo(void* pMemory);
	private:
		CHrMemoryRegister*  m_pRegister;

		CHrMemoryStack*     m_pMemoryStack;

		std::list<CHrPoolListener*> m_lisPoolListener;
	};
}



#endif // !_HR_POOLMANAGER_H_


