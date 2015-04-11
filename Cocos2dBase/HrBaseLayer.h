#ifndef _HR_BASELAYER_H_
#define _HR_BASELAYER_H_

#include "cocos2d.h"
#include "HrCCCom.h"

USING_NS_CC;

namespace HrCCBase
{
	class CHrBaseLayer : public cocos2d::Layer
	{
	protected:
		CHrBaseLayer();
		virtual ~CHrBaseLayer();

	public:
		//先无视原来的init
		virtual bool HrInit() = 0;

		//inher
		virtual bool onTouchBegan( Touch *touch, Event *unused_event ) override;
		virtual void onTouchMoved( Touch *touch, Event *unused_event ) override;
		virtual void onTouchEnded( Touch *touch, Event *unused_event ) override;
		virtual void onTouchCancelled( Touch *touch, Event *unused_event ) override;

		virtual void onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event ) override;
		virtual void onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event ) override;
		virtual void onTouchesEnded( const std::vector<Touch*>& touches, Event *unused_event ) override;
		virtual void onTouchesCancelled( const std::vector<Touch*>&touches, Event *unused_event ) override;

	};

}





#endif

