#include "HrPoolManager.h"
#include "cocos2d.h"
#include "../../HrCommon/HrMacros.h"
#include "HrMemoryStack.h"
#include "HrMemoryRegister.h"
#include "HrNew.h"

using namespace HrPool;
USING_NS_CC;

CHrPoolManager::CHrPoolManager(bool bOpenRegister) 
{
	m_pMemoryStack = new CHrMemoryStack();
	m_pRegister = nullptr;
	if (bOpenRegister)
	{
		m_pRegister = new CHrMemoryRegister();
	}
}

CHrPoolManager::~CHrPoolManager()
{
	CC_SAFE_DELETE( m_pMemoryStack );
	CC_SAFE_DELETE(m_pRegister);

	HRLOG(_HDEBUG, "HPOOL", "Hr Memory Pool close.\n");
}

void* CHrPoolManager::Malloc(uint64 nSize, char* szInfo /*= NULL */)
{
	void* pRetMemory = nullptr;
	pRetMemory = m_pMemoryStack->Mallock( nSize );
	if (pRetMemory != nullptr)
	{
		RegisterMemoryInfo( pRetMemory, szInfo );
	}

	return pRetMemory;
}

void CHrPoolManager::Free( void* pMemory )
{
	m_pMemoryStack->Free( pMemory );

	if (pMemory != nullptr)
	{
		UnRegisteMemoryInfo( pMemory );
	}
}

void CHrPoolManager::RegisterMemoryInfo( void* pMemory, char* szInfo )
{
	if (pMemory != nullptr && m_pRegister != nullptr && szInfo != nullptr)
	{
		m_pRegister->Add( pMemory, szInfo );
	}
}

void CHrPoolManager::UnRegisteMemoryInfo( void* pMemory )
{
	if (pMemory != nullptr && m_pRegister != nullptr)
	{
		m_pRegister->Del( pMemory );
	}
}

void CHrPoolManager::PrintTree()
{
	m_pMemoryStack->PrintStack();
}

void CHrPoolManager::PrintInfo()
{
	if (m_pRegister != nullptr)
	{
		m_pRegister->PrintInfo();
	}

	m_pMemoryStack->PrintInfo();
}

void CHrPoolManager::Release()
{

}

