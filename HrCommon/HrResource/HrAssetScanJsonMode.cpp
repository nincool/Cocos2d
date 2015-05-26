#include "HrAssetScanJsonMode.h"
#include "IAssetScanMode.h"
#include "IAssetLoadEvent.h"
#include "cocos2d.h"
#include "HrMacros.h"
#include "json/document.h"

using namespace HrCCBase;
using namespace std;
USING_NS_CC;

CHrAssetScanJsonMode::CHrAssetScanJsonMode()
{

}

CHrAssetScanJsonMode::~CHrAssetScanJsonMode()
{
}

void HrCCBase::CHrAssetScanJsonMode::Init(std::string& strJsonFilePath)
{
	m_strJsonFilePath = FileUtils::getInstance()->fullPathForFilename(strJsonFilePath);
	HRLOG("AssetScanJsonMode FilePath: %s", m_strJsonFilePath.c_str());
}

void HrCCBase::CHrAssetScanJsonMode::ScanningAssert()
{
	ssize_t size = 0;
	string strFileData = FileUtils::getInstance()->getStringFromFile(m_strJsonFilePath);
	if (strFileData.empty())
	{
		CCASSERT(nullptr, "AssetScanJsonMode Error! Empty file data! ");
	}

	rapidjson::Document d;
	d.Parse<0>(strFileData.c_str());
	if (d.HasParseError())
	{
		CCASSERT(nullptr, "Json ParseError!");
	}
	
	for (auto item = d.MemberonBegin(); item != d.MemberonEnd(); ++item)
	{
		string strKey = item->name.GetString();
		string strValue = item->value.GetString();
		if (strValue.length() == 0)
		{
			CCASSERT(nullptr, "Asset'path is empty");
			m_mapAssetPaths[strKey] = "";
		}
		else
		{
			m_mapAssetPaths[strKey] = strValue;
		}
	}
}

bool HrCCBase::CHrAssetScanJsonMode::IsFinished()
{
	return false;
}

const std::unordered_map<std::string, std::string>& HrCCBase::CHrAssetScanJsonMode::GetAssertPath()
{
	return m_mapAssetPaths;
}
