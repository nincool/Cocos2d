#include "HrDeviceFacade.h"
#include <cstring>
#include <string>
#include "cocos2d.h"
#define  LOG_TAG    "CCDeviceFacade_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
using namespace std;

// sharedApplication pointer
static CHrDeviceFacade* sm_pSharedDevice = 0;
char rtStr[128];
CHrDeviceFacade::CHrDeviceFacade()
{
}

CHrDeviceFacade::~CHrDeviceFacade()
{
    CC_ASSERT(this == sm_pSharedDevice);
    sm_pSharedDevice = NULL;
}


CHrDeviceFacade* CHrDeviceFacade::sharedDevice()
{
	if (!sm_pSharedDevice) {
		sm_pSharedDevice = new CHrDeviceFacade();
	}
	return sm_pSharedDevice;
}

const char* CHrDeviceFacade::myDeviceVersion(void)
{
	return "fuckallfuckallfuckallfuckall";
}

const char* CHrDeviceFacade::myOSVersion(void)
{
	return "Windows";
}

const char* CHrDeviceFacade::myGetUniId()
{
	return "dfhhthrer4r45454";
}
const bool CHrDeviceFacade::myFindFileAtDisk(const char* AvatarFile)
{
	bool bRet = false;
	FILE* fs = fopen(AvatarFile, "r");
	if (fs != NULL)
	{
		bRet = true;
		fclose(fs);
	}

	return bRet;
}
const char* CHrDeviceFacade::myGetAvatarSavePath()
{
	return "d:/Picture";
}
const char* CHrDeviceFacade::getIMEI()
{
	return "IMEI_PC";
}

const char* CHrDeviceFacade::getPhoneNoAndProvider()
{
	return "65445646131544312215854";
}
const char* CHrDeviceFacade::getPhoneNo()
{
	return "13800138000";
}
const char* CHrDeviceFacade::getProvider()
{
	return "01";
}
//distribution channel id
const char* CHrDeviceFacade::getDistriChannelID()
{
	return "unknown";
}
const char* CHrDeviceFacade::getDistriChannelIDNew()
{
	return "1";
}
void CHrDeviceFacade::myExtraAction(int nAction, int arg1)
{

}
void CHrDeviceFacade::UpdateGameApk(const char* apkUrlAndroid, const char* apkUrlIOS)
{
}
void CHrDeviceFacade::CreateAvatarRet(const char *pszResourcePath)
{
}
void CHrDeviceFacade::mySendSMS(const char* phoneNo, const char* smsContent)
{
}
void CHrDeviceFacade::J2CStringRet(const char *pszKey, const char *pszValue1, const char *pszValue2)
{
}
const char* CHrDeviceFacade::myCallAlixpay(const char* orderInfo)
{
	return "";
}
const char* CHrDeviceFacade::myCallwiipay(const char* orderInfo)
{
	return "";
}
void CHrDeviceFacade::downloadAPK(const char* orderInfo, const char* fileName)
{
}
void CHrDeviceFacade::OpenUrlByBrowserView(const char* strUrl)
{
	string strstrUrl = strUrl;
	//ShellExecuteA(NULL,   "open ",   strstrUrl.c_str(),   NULL,   NULL,   SW_SHOWNORMAL);
}
const char* CHrDeviceFacade::myCallshenzhoufu(const char* orderInfo, const char* orderInfo2)
{
	return "";
}
const char* CHrDeviceFacade::getStringByKey(const char* strKey)
{
	CCLOG("CCDeviceFacade::getStringByKey%s",strKey);
	return "";
}
const char* CHrDeviceFacade::getStringByKey2(const char* strKey, const char* strValue)
{
	CCLOG("CCDeviceFacade::getStringByKey%s",strKey);
	return "";
}
const char* CHrDeviceFacade::getStringByKey3(const char* strKey, const char* strValue, const char* strValue2)
{
	CCLOG("CCDeviceFacade::getStringByKey%s",strKey);
	return "";
}
//0网络不可用 1 可用
const char* CHrDeviceFacade::getNetworkState()
{
	return "";
}

const char* CHrDeviceFacade::GetMACAddresses()
{
	return "";
}

