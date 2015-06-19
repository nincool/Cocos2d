#ifndef _HR_ASSETRESOURCELOAD_H_
#define _HR_ASSETRESOURCELOAD_H

#include "IAssetLoad.h"
#include "cocos2d.h"

#include <unordered_map>
#include <string>
#include "../../HrCommon/HrCCBase/HrBasicType.h"

#define LOAD_PLIST_NUM_PER_FRAME 5

namespace HrCCBase
{
	class IAssetScanMode;
	class IAssetLoadEvent;
	class CHrAssetPlistLoad : public IAssetLoad
	{
	public:
		CHrAssetPlistLoad();
		~CHrAssetPlistLoad();

	public:
		virtual void InitAssetLoad(IAssetScanMode* assetScanMode, IAssetLoadEvent* assetLoadEvent) override;
		virtual void LoadOneResource() override;
		virtual int GetTotalAssetNum() override;

		void DemandAssetPaths(std::unordered_map<std::string, std::string>& mapAssetPath);
	private:
		void LoadResourceCallBack();
	private:
		IAssetScanMode*  m_pAssetScanMode;
		IAssetLoadEvent* m_pAssetLoadEvent;

		std::unordered_map<std::string, std::string> m_mapAssetPaths;
		std::unordered_map<std::string, std::string>::iterator m_iteCurrentPos;

		std::unordered_map<std::string, std::string> m_mapPlistPaths;
		std::unordered_map<std::string, std::string>::iterator m_iteCurPlistPos;
		
		//待加载资源总数
		uint32 m_nTotalNum;
		//当前资源加载数量
		uint32 m_nCurrentNum;
	};
}



#endif // !_HR_ASSETRESOURCELOAD_H_



