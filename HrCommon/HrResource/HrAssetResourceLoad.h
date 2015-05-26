#ifndef _HR_ASSETRESOURCELOAD_H_
#define _HR_ASSETRESOURCELOAD_H

#include "IAssetLoad.h"

namespace HrCCBase
{
	class CHrAssetResourceLoad : public IAssetLoad
	{
	public:
		CHrAssetResourceLoad(){};
		~CHrAssetResourceLoad(){};

	public:
		virtual void StartLoad(const IAssetScaneMode* assetScanMode, const IAssetLoadEvent* assetLoadEvent) override;
	};
}



#endif // !_HR_ASSETRESOURCELOAD_H_



