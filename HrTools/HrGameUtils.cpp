#include "HrGameUtils.h"
#include <ctime>

using namespace std;
USING_NS_CC;

string CHrGameUtils::GetDataNow()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday( &now, NULL );
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime( &tp );
	char date[32] = { 0 };
	sprintf( date, "%d-%02d-%02d", (int)tm->tm_year + 1900,
		(int)tm->tm_mon + 1, (int)tm->tm_mday );
	return string( date );
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm *tm;
	time_t timep;
	time( &timep );
	tm = localtime( &timep );
	//int year = tm->tm_year + 1900;  
	//int month = tm->tm_mon + 1;  
	//int day = tm->tm_mday;  
	//int hour=tm->tm_hour;  
	//int minute=tm->tm_min;  
	//int second=tm->tm_sec;
	char time[64] = { 0 };
	sprintf( time, "%d-%02d-%02d %02d:%02d:%02d", (int)tm->tm_year + 1900,
		(int)tm->tm_mon + 1, (int)tm->tm_mday, (int)tm->tm_hour,
		(int)tm->tm_min, (int)tm->tm_sec );
	return string( time );
#endif
}

unsigned long long CHrGameUtils::GetTimeTickCount()
{
	std::clock_t clockTime = std::clock();
	unsigned long long nTicks = (double)clockTime / CLOCKS_PER_SEC * 1000;
	return nTicks;
}

cocos2d::Vec2 CHrGameUtils::GetNodeCenterPosition(cocos2d::Node* pNdoe)
{
	return Vec2(pNdoe->getContentSize().width / 2, pNdoe->getContentSize().height / 2);
}
