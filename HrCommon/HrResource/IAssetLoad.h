#ifndef _IASSETLOAD_H_
#define _IASSETLOAD_H_

namespace HrCCBase
{
	class IAssetScaneMode;
	class IAssetLoadEvent;
	class IAssetLoad
	{
	public:
		virtual ~IAssetLoad(){};

	public:
		virtual void StartLoad(const IAssetScaneMode* assetScanMode, const IAssetLoadEvent* assetLoadEvent) = 0;
	};
}

#endif
