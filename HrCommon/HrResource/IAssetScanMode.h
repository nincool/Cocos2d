#ifndef _IASSETSCANMODE_H_
#define _IASSETSCANMODE_H_

#include <unordered_map>
#include <string>

namespace HrCCBase
{
	class IAssetScaneMode
	{
	public:
		virtual ~IAssetScaneMode(){};

	public:
		/**
		 *	@Comment: 资源扫描 [5/25/2015 By Hr]
		*/
		virtual void ScanningAssert() = 0;
		
		/**
		 *	@Comment: 资源路径扫描是否完成 [5/25/2015 By Hr]
		 *	@Return: true or false
		*/
		virtual bool IsFinished() = 0;
		
		/**
		 *	@Comment: 获取资源路径 [5/25/2015 By Hr]
		 *	@Return: vector<string> 包含资源路径
		*/
		virtual const std::unordered_map<std::string, std::string>& GetAssertPath() = 0;
	};
}

#endif