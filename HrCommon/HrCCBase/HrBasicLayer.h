#ifndef _HR_BASELAYER_H_
#define _HR_BASELAYER_H_

#include "cocos2d.h"
#include "HrCCCom.h"

USING_NS_CC;

namespace HrCCBase
{
	class CHrBasicLayer : public cocos2d::Layer
	{
	protected:
		CHrBasicLayer();
		virtual ~CHrBasicLayer();

	public:
		virtual bool init() override;

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

