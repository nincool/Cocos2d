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
		 *	@Comment: ��Դɨ�� [5/25/2015 By Hr]
		*/
		virtual void ScanningAssert() = 0;
		
		/**
		 *	@Comment: ��Դ·��ɨ���Ƿ���� [5/25/2015 By Hr]
		 *	@Return: true or false
		*/
		virtual bool IsFinished() = 0;
		
		/**
		 *	@Comment: ��ȡ��Դ·�� [5/25/2015 By Hr]
		 *	@Return: vector<string> ������Դ·��
		*/
		virtual const std::unordered_map<std::string, std::string>& GetAssertPath() = 0;
	};
}

#endif