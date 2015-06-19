#include "HrAssetLoadManager.h"
#include "IAssetLoad.h"

using namespace HrCCBase;

HrCCBase::CHrAssetLoadManager::CHrAssetLoadManager()
{
	m_nCurLoadAssetNum = 0;
	m_nTotalAssetNum = 0;
	m_nCurLoadAssetIndex = 0;
	m_pAssetLoadEvent = nullptr;
}

HrCCBase::CHrAssetLoadManager::~CHrAssetLoadManager()
{

}

void CHrAssetLoadManager::ScanResource()
{
	for (auto item : m_vecAssetLoad)
	{
		m_nTotalAssetNum += item->GetTotalAssetNum();
	}
}

void CHrAssetLoadManager::UpdateLoadResource()
{
	if (m_vecAssetLoad.size() > 0)
	{
		m_vecAssetLoad[m_nCurLoadAssetIndex]->LoadOneResource();
	}
}

void CHrAssetLoadManager::SetCurrentProcess(int nTotalNum, int nCurrentNum)
{
	++m_nCurLoadAssetNum;
	m_pAssetLoadEvent->SetCurrentProcess(m_nTotalAssetNum, m_nCurLoadAssetNum + 1 );
}

void CHrAssetLoadManager::LoadAssetFinal()
{
	++m_nCurLoadAssetIndex;
	if (m_nCurLoadAssetNum >= m_nTotalAssetNum)
	{
		m_pAssetLoadEvent->LoadAssetFinal();
	}
}
