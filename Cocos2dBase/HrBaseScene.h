#ifndef _HR_BASESCENE_H_
#define _HR_BASESCENE_H_

#include "cocos2d.h"
#include "HrCCCom.h"

USING_NS_CC;

namespace HrCCBase
{
	class CHrBaseScene : public cocos2d::Scene
	{
	public:
		CHrBaseScene();
		virtual ~CHrBaseScene();

	public:
		virtual bool HrInit() = 0;
	};
}


#endif




