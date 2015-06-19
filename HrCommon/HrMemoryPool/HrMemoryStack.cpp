#include "HrMemoryStack.h"
#include "HrMemoryStackToken.h"
#include "cocos2d.h"
#include "../../HrCommon/HrMacros.h"

using namespace HrPool;
USING_NS_CC;

CHrMemoryStack::CHrMemoryStack( )
{
	m_pStackTokenHead = new CHrMemoryStackToken( HR_MEM_BLOCK_MIN);

	m_nMaxMemoryAddress = 0;
	m_nAllBlockCount = 0;
	m_nMemoryUsed = 0;
	m_bCloseFlag = false;

}

CHrMemoryStack::~CHrMemoryStack()
{
	HRLOG(_HDEBUG, "HPOOL", "Memory Stack: Max Point = 0x%p\n", m_nMaxMemoryAddress);

	CC_SAFE_DELETE( m_pStackTokenHead );
}

void* CHrMemoryStack::Mallock(uint64 nSize)
{
	void* pRetMemory = nullptr;
	if (0 >= nSize)
	{
		HRLOG(_HDEBUG, "HPOOL", "CHrMemoryStack::Mallock Error! Mallock MemorySize[%d]", nSize);

		return pRetMemory;
	}
	
	if (m_pStackTokenHead != nullptr)
	{
		pRetMemory = m_pStackTokenHead->Malloc( nSize, m_nAllBlockCount, m_nMemoryUsed );
		if (m_nMaxMemoryAddress < reinterpret_cast<uint64>(pRetMemory))
		{
			m_nMaxMemoryAddress = reinterpret_cast<uint64>(pRetMemory);
		}

		return pRetMemory;
	}

	return pRetMemory;
}

bool CHrMemoryStack::Free( void* pMemory )
{
	bool bRetVal = m_pStackTokenHead->Free( pMemory, m_bCloseFlag );

	return bRetVal;
}

void CHrMemoryStack::PrintStack()
{
	m_pStackTokenHead->PrintStack();
}

void CHrMemoryStack::PrintInfo()
{
	HRLOG(_HDEBUG, "HPOOL", "block=%d, use=%d kbytes, biggest=%p\n"
		, m_nAllBlockCount
		, m_nMemoryUsed / 1024
		, m_nMaxMemoryAddress);
}
