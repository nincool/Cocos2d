#ifndef _IASSETLOADEVENT_H_
#define _IASSETLOADEVENT_H_

namespace HrCCBase
{
	class IAssetLoadEvent
	{
	public:
		virtual ~IAssetLoadEvent(){};
		
	public:
		/**
		 *	@Comment: 当前进度回调 [5/25/2015 By Hr]
		*/
		virtual void SetCurrentProcess(int nTotalNum, int nCurrentNum);

		/**
		 *	@Comment: 资源加载完成回调 [5/25/2015 By Hr]
		*/
		virtual void LoadAssetFinal();
	};
}

#endif