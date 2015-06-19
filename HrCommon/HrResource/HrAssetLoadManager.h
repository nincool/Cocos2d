#ifndef _HR_ASSETLOADMANAGER_H_
#define _HR_ASSETLOADMANAGER_H_

#include "IAssetLoadEvent.h"
#include <vector>

namespace HrCCBase
{
	class IAssetLoad;
	class CHrAssetLoadManager : public HrCCBase::IAssetLoadEvent
	{
	public:
		CHrAssetLoadManager();
		~CHrAssetLoadManager();

	public:

		void ScanResource();

		void UpdateLoadResource();

		virtual void SetCurrentProcess(int nTotalNum, int nCurrentNum);

		virtual void LoadAssetFinal();
	public:
		std::vector<IAssetLoad*> m_vecAssetLoad;

		IAssetLoadEvent* m_pAssetLoadEvent;

		int m_nTotalAssetNum;
		int m_nCurLoadAssetNum;

	private:
		int m_nCurLoadAssetIndex;
	};

}


#endif // !_HR_ASSETLOADMANAGER_H_


