/************************************************************************
*
* @Comment：全局静态单利对象在使用内存池的时候一定要注意析构顺序！！
最好继承内存池侦听接口，后面可以参考loki实现指定析构顺序
*
* @Author: Hr
* @Date: [6/9/2015 By Hr]
*
************************************************************************/
#ifndef _HR_NEW_H_
#define _HR_NEW_H_

#include "HrPoolManager.h"
#include <memory>
#include <list>

namespace HrPool
{
	class CHrNew
	{
	public:
		CHrNew(){};
		~CHrNew()
		{
		};

	public:
		static void* New(uint64 nSize, const char* file, int line);


		static void Delete(void* pMemory)
		{
			m_s_pPoolManager->Free(pMemory);
		}

		static void DestoryMemoryManager()
		{
			//m_s_pPoolManager.reset();
		}

		static void PrintMemoryInfo()
		{
			m_s_pPoolManager->PrintInfo();
			m_s_pPoolManager->PrintTree();
		}

		static void SetPoolManager(CHrPoolManager* pPoolManager)
		{
			if (m_s_pPoolManager != nullptr)
			{
				//异常
			}
			m_s_pPoolManager = pPoolManager;
		}

	private:
		static CHrPoolManager* m_s_pPoolManager;
	};
}



#endif // !_HR_NEW_H_


