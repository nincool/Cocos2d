#ifndef _HR_RANDUTILS_H_
#define _HR_RANDUTILS_H_

#include "../HrCommon/HrCCBase/HrBasicType.h"

class CHrRandUtils
{
public:
	CHrRandUtils();
	~CHrRandUtils();

public:
	/**
	 *	@Comment: ��ȡһ������� nMin <= Rt <= nMax [6/1/2015 By Hr]
	*/
	static uint GetUnsignedRandNum(uint nMin, uint nMax);
};



#endif // !_HR_RANDUTILS_H_

