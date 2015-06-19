#ifndef _HR_BASESCENE_H_
#define _HR_BASESCENE_H_

#include "cocos2d.h"


namespace HrCCBase
{
	class CHrBasicScene : public cocos2d::Scene
	{
	public:
		CHrBasicScene();
		virtual ~CHrBasicScene();

	public:
		virtual bool init() override;
	};
}


#endif




