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
		 *	@Comment: ��Դɨ�� [5/25/2015 By Hr]
		*/
		virtual void ScanningAssert() = 0;
		
		/**
		 *	@Comment: ��ȡ��Դ·�� [5/25/2015 By Hr]
		 *	@Return: vector<string> ������Դ·��
		*/
		virtual void GetAssertPath(std::unordered_map<std::string, std::string>& mapPath) = 0;
	};
}

#endif