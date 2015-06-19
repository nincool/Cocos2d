#ifndef __CC_CCDeviceFacade_H__
#define __CC_CCDeviceFacade_H__


//class CCRect;
class  CHrDeviceFacade
{
public:
	CHrDeviceFacade();
	virtual ~CHrDeviceFacade();

	static CHrDeviceFacade* sharedDevice();
public:
	const char* myDeviceVersion( void );
	const char* myOSVersion( void );
	const char* myGetUniId();
	const bool myFindFileAtDisk(const char* AvatarFile);
	const char* myCallAlixpay(const char* orderInfo);
	const char* myCallwiipay(const char* orderInfo);
	void downloadAPK(const char* orderInfo,const char* fileName);
	const char* myCallshenzhoufu(const char* orderInfo,const char* orderInfo2);
	const char* myGetAvatarSavePath();
	const char* getIMEI();
	//get phone No  and Telecom service providers
	const char* getPhoneNoAndProvider();
	//02���й��ƶ���01���й���ͨ��03���й�����  ���ַ��� ����δ֪
	const char* getProvider();
	//distribution channel id
	const char* getDistriChannelID();
	const char* getDistriChannelIDNew();
	//0���粻���� 1����
	const char* getNetworkState();
	void mySendSMS(const char* phoneNo,const char* smsContent);
	const char* getPhoneNo();

	void myExtraAction(int nAction,int arg1);
	static void UpdateGameApk(const char* apkUrlAndroid,const char* apkUrlIOS);

	void OpenUrlByBrowserView(const char* strUrl);
	//ͷ��ѡ��ɹ��� �豸��������ͷ��·��
	void CreateAvatarRet(const char *pszResourcePath);
	void J2CStringRet(const char *pszKey,const char *pszValue1,const char *pszValue2);

	const char* getStringByKey(const char* strKey);
	const char* getStringByKey2(const char* strKey,const char* strValue);
	const char* getStringByKey3(const char* strKey,const char* strValue,const char* strValue2);

	const char* GetMACAddresses();

};
#endif    // __CC_CCDeviceFacade_H__
