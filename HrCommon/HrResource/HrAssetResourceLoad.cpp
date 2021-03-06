#include "HrAssetResourceLoad.h"
#include "IAssetLoadEvent.h"
#include "IAssetScanMode.h"

using namespace HrCCBase;
using namespace std;
USING_NS_CC;

CHrAssetResourceLoad::CHrAssetResourceLoad()
{
	m_pAssetScanMode = nullptr;
	m_pAssetLoadEvent = nullptr;
	
	m_nTotalNum = 0;
	m_nCurrentNum = 0;
}

CHrAssetResourceLoad::~CHrAssetResourceLoad()
{
}

void HrCCBase::CHrAssetResourceLoad::InitAssetLoad(IAssetScanMode* assetScanMode, IAssetLoadEvent* assetLoadEvent)
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

int CHrAssetResourceLoad::GetTotalAssetNum()
{
	return m_nTotalNum;
}

void CHrAssetResourceLoad::DemandAssetPaths(std::unordered_map<std::string, std::string>& mapAssetPath)
{
	mapAssetPath.swap(m_mapAssetPaths);
}

void CHrAssetResourceLoad::LoadOneResource()
{
	//如果没有资源加载，那么直接结束
	if (m_nTotalNum == 0)
	{
		m_pAssetLoadEvent->LoadAssetFinal();
	}

	//这里可以做一个阶梯优化
	for (uint i = 0; i < 3; ++i)
	{
		if (m_iteCurrentPos != m_mapAssetPaths.end())
		{
			std::string& strPath = m_iteCurrentPos->second;
			++m_iteCurrentPos;

			CCLOG("Load One Resource: %s", strPath.c_str());
			Director::getInstance()->getTextureCache()->addImageAsync(strPath, CC_CALLBACK_1(CHrAssetResourceLoad::LoadResourceCallBack, this));
		}
	}
}

void HrCCBase::CHrAssetResourceLoad::LoadResourceCallBack(Texture2D* texture)
{
	CCASSERT(texture != nullptr, "loaded Texture is null");
	CCLOG("Load Resource CallBack!!! Load Num:%d TotalNum:%d All Num:%d", m_nCurrentNum, m_nTotalNum, m_mapAssetPaths.size());

	++m_nCurrentNum;
	m_pAssetLoadEvent->SetCurrentProcess(m_nTotalNum, m_nCurrentNum);
	
	if (m_nCurrentNum >= m_nTotalNum)
	{
		m_pAssetLoadEvent->LoadAssetFinal();
	}
}
