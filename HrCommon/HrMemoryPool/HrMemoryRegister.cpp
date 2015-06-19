#include "HrMemoryRegister.h"
#include "cocos2d.h"
#include "../../HrCommon/HrMacros.h"

using namespace HrPool;
USING_NS_CC;

#define HR_ZEROMEM(p, len) memset(p, 0, len)
#define HR_CLEAN_CHAR_BUFFER(p) (*((char*)(p))='\0')

CHrMemoryRegister::CHrMemoryRegister(  )
{
	m_nUsedMax = 0;
	m_nMemoryAddressCount = 0;
	m_pMaxMemoryAddress = nullptr;
}

CHrMemoryRegister::~CHrMemoryRegister()
{
	PrintInfo();
}

void CHrMemoryRegister::Add( void* pMemory, char* szInfo )
{
	if (pMemory > m_pMaxMemoryAddress)
	{
		m_pMaxMemoryAddress = pMemory;
	}

	for (int i = 0; i < m_nUsedMax; ++i)
	{
		if (m_registerArr[i].m_pMemory == nullptr)
		{
			++m_nMemoryAddressCount;
			RegisterCopy( &(m_registerArr[i]), pMemory, szInfo );

			return;
		}
	}

	if (HR_MEMORY_REGISTER_MAX <= m_nUsedMax)
	{
		HRLOG(_HDEBUG, "HPOOL", "*******ERROR******** CMemoryRegister is full Max[%d]!\n", m_nUsedMax);
		return;
	}

	RegisterCopy( &(m_registerArr[m_nUsedMax]), pMemory, szInfo );
	++m_nMemoryAddressCount;
	++m_nUsedMax;
}

void CHrMemoryRegister::RegisterCopy( SHrMemoryRegister* pDest, void* pMemory, char* szInfo )
{
	pDest->m_pMemory = pMemory;
	if (szInfo != nullptr)
	{
		HR_ZEROMEM(pDest->m_szInfo, HR_MEMORY_BLOCK_INFO_MAX_SIZE);
		memcpy( pDest->m_szInfo, szInfo, HR_MEMORY_BLOCK_INFO_MAX_SIZE-1 );
	}
	else
	{
		HR_CLEAN_CHAR_BUFFER( pDest->m_szInfo );
	}
}

void CHrMemoryRegister::Del( void* pMemory )
{
	for (int i = 0; i < m_nUsedMax; ++i)
	{
		if (pMemory == m_registerArr[i].m_pMemory)
		{
			--m_nMemoryAddressCount;
			m_registerArr[i].m_pMemory = nullptr;
			HR_CLEAN_CHAR_BUFFER( m_registerArr[i].m_szInfo );

			return;
		}
	}
}

void CHrMemoryRegister::Modify( void* pOld, void* pNew )
{
	for (int i = 0; i < m_nUsedMax; ++i)
	{
		if (pOld == m_registerArr[i].m_pMemory)
		{
			m_registerArr[i].m_pMemory = pNew;

			if (pNew > m_pMaxMemoryAddress)
			{
				m_pMaxMemoryAddress = pNew;
			}

			return;
		}
	}

	HRLOG(_HDEBUG, "HPOOL", "****ERROR**** CMemroyRegister::Modeify():I can't found point!\n");

	return;
}

void CHrMemoryRegister::PrintInfo()
{
	HRLOG(_HDEBUG, "HPOOL", "memory pool: %d / %d, the biggest = %p\n", m_nMemoryAddressCount, m_nUsedMax + 1, m_pMaxMemoryAddress);
	for (int i = 0; i < m_nUsedMax; ++i)
	{
		if (m_registerArr[i].m_pMemory != nullptr)
		{
			HRLOG(_HERROR, "HPOOL", "Lost:%s", m_registerArr[i].m_szInfo);
		}

	}
}




