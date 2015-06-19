#include "HrRandUtils.h"
#include "cocos2d.h"

USING_NS_CC;

CHrRandUtils::CHrRandUtils()
{
}


CHrRandUtils::~CHrRandUtils()
{
}

uint CHrRandUtils::GetUnsignedRandNum(uint nMin, uint nMax)
{
	float fRandNum = CCRANDOM_0_1();
	uint nRtNum = (nMax - nMin) * fRandNum + nMin;

	return nRtNum;
}
