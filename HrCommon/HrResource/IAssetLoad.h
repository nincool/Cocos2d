#ifndef _IASSETLOAD_H_
#define _IASSETLOAD_H_

namespace HrCCBase
{
	class IAssetScanMode;
	class IAssetLoadEvent;
	class IAssetLoad
	{
	public:
		virtual ~IAssetLoad(){};

	public:
		virtual void InitAssetLoad(IAssetScanMode* assetScanMode, IAssetLoadEvent* assetLoadEvent) = 0;
		virtual void LoadOneResource() = 0;
		virtual int GetTotalAssetNum() = 0;
	};
}

#endif
