#ifndef _HR_MACROS_H_
#define _HR_MACROS_H_

#include "cocos2d.h"



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define HRLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)//如果可变参数被忽略或为空，’##’操作将使预处理器(preprocessor)去除掉它前面的那个
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
#define HRLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)//如果可变参数被忽略或为空，’##’操作将使预处理器(preprocessor)去除掉它前面的那个
#else 
#define HRLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)//如果可变参数被忽略或为空，’##’操作将使预处理器(preprocessor)去除掉它前面的那个
#endif

#endif

