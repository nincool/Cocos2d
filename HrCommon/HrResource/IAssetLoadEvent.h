#ifndef _IASSETLOADEVENT_H_
#define _IASSETLOADEVENT_H_

namespace HrCCBase
{
	class IAssetLoadEvent
	{
	public:
		IAssetLoadEvent(){};
		virtual ~IAssetLoadEvent(){};
		
	public:
		/**
		 *	@Comment: 当前进度回调 [5/25/2015 By Hr]
		*/
		virtual void SetCurrentProcess(int nTotalNum, int nCurrentNum) = 0;

		/**
		 *	@Comment: 资源加载完成回调 [5/25/2015 By Hr]
		*/
		virtual void LoadAssetFinal() = 0;
	};
}

#endif