#ifndef _HR_ASSETSCANJSONMODE_H_
#define _HR_ASSETSCANJSONMODE_H_

#include "IAssetScanMode.h"
#include <string>


namespace HrCCBase
{
	class CHrAssetScanJsonMode : public IAssetScaneMode
	{
	public:
		CHrAssetScanJsonMode();
		~CHrAssetScanJsonMode();

		void Init(std::string& strJsonFilePath);
	public:

		virtual void ScanningAssert() override;

		virtual bool IsFinished() override;

		virtual const std::unordered_map<std::string, std::string>& GetAssertPath() override;
	private:
		std::string m_strJsonFilePath;
		std::unordered_map<std::string, std::string> m_mapAssetPaths;
	};
}

#endif

