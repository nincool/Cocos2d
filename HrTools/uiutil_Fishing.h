#ifndef __UIUTIL_H__
#define __UIUTIL_H__

#include <string>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;


class uiutil
{
public:
	static string  getstr(const char *format,...);

	static int log(char *format,...);

	static int log1(char *format,...);

	static int log2(char *format,...);
};

#endif