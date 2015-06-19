#ifndef _HR_MACROS_H_
#define _HR_MACROS_H_

#include "cocos2d.h"
#include "HrLog/HrLog.h"


//Comon Tools
#define GET_ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define HRLOG(level, model, content, ...) CCLOG(content, ##__VA_ARGS__)
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
#define HRLOG(level, model, content, ...) \
	std::string strLogContent = StringUtils::format(content, ##__VA_ARGS__); \
	CHrLog::Instance().Log(level, model, strLogContent.c_str());

#else 
#define HRLOG(level, model, content, ...) CCLOG(content, ##__VA_ARGS__)//����ɱ���������Ի�Ϊ�գ���##��������ʹԤ������(preprocessor)ȥ������ǰ����Ǹ�
#endif

//cocos define
//#define GET_TEXTURE_FROM_CACHE(key) Director::getInstance()->getTextureCache()->getTextureForKey(GET_PATH_FROM_KEY(key))

#endif
