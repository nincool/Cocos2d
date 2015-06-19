#ifndef _HR_ASSETSCANJSONMODE_H_
#define _HR_ASSETSCANJSONMODE_H_

#include "IAssetScanMode.h"
#include <string>


namespace HrCCBase
{
	class CHrAssetScanJsonMode : public IAssetScanMode
	{
	public:
		CHrAssetScanJsonMode();
		virtual ~CHrAssetScanJsonMode();

		virtual void Init(std::string& strJsonFilePath) override;
	public:

		virtual void ScanningAssert() override;

		virtual void GetAssertPath(std::unordered_map<std::string, std::string>& mapPath) override;
	private:
		std::string m_strJsonFilePath;
		std::unordered_map<std::string, std::string> m_mapAssetPaths;
	};
}

#endif

