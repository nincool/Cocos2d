#ifndef _HR_CCTOOLS_H_
#define _HR_CCTOOLS_H_

#include "cocos2d.h"


template <typename T>
T* HrCreate()
{
	T* pT = new (std::nothrow) T();
	if (pT != nullptr && pT->HrInit())
	{
		return pT;
	}
	else
	{
		if (pT == nullptr)
			CCASSERT(nullptr, "FATAL: Not enough memory");
		else
			CCASSERT(nullptr, "FATAL: Init Error!");
		CC_SAFE_DELETE( pT );
	}

	return pT;
}

class CHrCCTools
{
public:
	CHrCCTools(){};
	~CHrCCTools(){};

	static std::string GetDataNow();

	//////////////////////////////////////////////////////////////////////////
	inline static bool IsWinPlatform()
	{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		return true;
#else
		return false;
#endif

	}

	inline static bool IsAndroidPlatform()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		return true;
#endif
		return false;
	}

	inline static bool IsIOSPlatform()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		return true;
#endif
		return false;
	}
};



#endif

