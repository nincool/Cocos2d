#include "HrAssetPlistLoad.h"
#include "IAssetLoadEvent.h"
#include "IAssetScanMode.h"

using namespace HrCCBase;
using namespace std;
USING_NS_CC;

CHrAssetPlistLoad::CHrAssetPlistLoad()
{
	m_pAssetScanMode = nullptr;
	m_pAssetLoadEvent = nullptr;
	
	m_nTotalNum = 0;
	m_nCurrentNum = 0;
}

CHrAssetPlistLoad::~CHrAssetPlistLoad()
{
}

void HrCCBase::CHrAssetPlistLoad::InitAssetLoad(IAssetScanMode* assetScanMode, IAssetLoadEvent* assetLoadEvent)
{
	m_pAssetScanMode = assetScanMode;
	m_pAssetLoadEvent = assetLoadEvent;

	m_pAssetScanMode->ScanningAssert();
	m_pAssetScanMode->GetAssertPath(m_mapAssetPaths);
	m_iteCurrentPos = m_mapAssetPaths.begin();

	m_nTotalNum = m_mapAssetPaths.size();
	CCASSERT(m_nTotalNum != 0, "The num of resource is 0");
	m_nCurrentNum = 0;
}

int CHrAssetPlistLoad::GetTotalAssetNum()
{
	if (m_nTotalNum == 0)
	{
		return 0;
	}
	float fLoadFrameNum = (float)m_nTotalNum / LOAD_PLIST_NUM_PER_FRAME;
	
	uint32 nLoadFrameNum = fLoadFrameNum;
	m_nTotalNum = nLoadFrameNum + (m_nTotalNum > nLoadFrameNum * LOAD_PLIST_NUM_PER_FRAME ? 1 : 0);
	
	return m_nTotalNum;
}

void CHrAssetPlistLoad::DemandAssetPaths(std::unordered_map<std::string, std::string>& mapAssetPath)
{
	mapAssetPath.swap(m_mapAssetPaths);
}

void CHrAssetPlistLoad::LoadOneResource()
{
	if (m_nTotalNum == 0)
	{
		m_pAssetLoadEvent->LoadAssetFinal();
	}

	for (int i = 0; i < LOAD_PLIST_NUM_PER_FRAME; ++i)
	{
		if (m_iteCurrentPos != m_mapAssetPaths.end())
		{
			std::string& strPath = m_iteCurrentPos->second;
			++m_iteCurrentPos;

			CCLOG("Load One Resource: %s", strPath.c_str());
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(strPath);
		}
	}
	LoadResourceCallBack();
}

void HrCCBase::CHrAssetPlistLoad::LoadResourceCallBack()
{
	CCLOG("Load Resource CallBack!!! Load Num:%d All Num:%d", m_nCurrentNum, m_mapAssetPaths.size());

	++m_nCurrentNum;
	m_pAssetLoadEvent->SetCurrentProcess(m_nTotalNum, m_nCurrentNum);
	
	if (m_nCurrentNum >= m_nTotalNum)
	{
		m_pAssetLoadEvent->LoadAssetFinal();
	}
}
