#ifndef _HR_MACROS_H_
#define _HR_MACROS_H_

#include "cocos2d.h"



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define HRLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)//����ɱ���������Ի�Ϊ�գ���##��������ʹԤ������(preprocessor)ȥ������ǰ����Ǹ�
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
#define HRLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)//����ɱ���������Ի�Ϊ�գ���##��������ʹԤ������(preprocessor)ȥ������ǰ����Ǹ�
#else 
#define HRLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)//����ɱ���������Ի�Ϊ�գ���##��������ʹԤ������(preprocessor)ȥ������ǰ����Ǹ�
#endif

#endif

