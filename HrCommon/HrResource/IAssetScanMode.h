#ifndef _IASSETSCANMODE_H_
#define _IASSETSCANMODE_H_

#include <unordered_map>
#include <string>

namespace HrCCBase
{
	class IAssetScanMode
	{
	public:
		IAssetScanMode(){};
		virtual ~IAssetScanMode(){};

	public:
		virtual void Init(std::string& strPath) = 0;
		/**
		 *	@Comment: 资源扫描 [5/25/2015 By Hr]
		*/
		virtual void ScanningAssert() = 0;
		
		/**
		 *	@Comment: 获取资源路径 [5/25/2015 By Hr]
		 *	@Return: vector<string> 包含资源路径
		*/
		virtual void GetAssertPath(std::unordered_map<std::string, std::string>& mapPath) = 0;
	};
}

#endif