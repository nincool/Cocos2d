#include "HrNew.h"

using namespace HrPool;

//³õÊ¼»¯ÄÚ´æ³Ø
CHrPoolManager* CHrNew::m_s_pPoolManager = nullptr;

bool GetEndStringWithChar(char* p, char c)
{
	char* pFlag = strrchr(p, c);
	if (pFlag != NULL)
	{
		//*(pFlag) = '\0';
		memcpy(p, pFlag, strlen(pFlag));
		*(p + strlen(pFlag)) = '\0';
		return true;
	}

	return false;
}

void* HrPool::CHrNew::New(uint64 nSize, const char* file, int line)
{
		char* pInfo = nullptr;
#ifdef WIN32
#ifdef _DEBUG
		char szBuffer[1024];
		memset(szBuffer, 0, sizeof(szBuffer));
		sprintf(szBuffer, "%s Line:%d", file, line);
		GetEndStringWithChar(szBuffer, '\\');
		pInfo = &(szBuffer[0]);
#endif // _DEBUG

#endif // WIN32 && #def

		if (m_s_pPoolManager == nullptr)
		{
			return nullptr;
		}

		void* pRetMemory = m_s_pPoolManager->Malloc(nSize, pInfo);
		return pRetMemory;
}
