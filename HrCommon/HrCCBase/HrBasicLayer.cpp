#include "HrBasicLayer.h"

using namespace HrCCBase;

CHrBasicLayer::CHrBasicLayer()
{
}

CHrBasicLayer::~CHrBasicLayer()
{
}


bool HrCCBase::CHrBasicLayer::init()
{
	Layer::init();
}


bool CHrBasicLayer::onTouchBegan( Touch *touch, Event *unused_event )
{
	return false;
}

void CHrBasicLayer::onTouchMoved( Touch *touch, Event *unused_event )
{

}

void CHrBasicLayer::onTouchEnded( Touch *touch, Event *unused_event )
{

}

void CHrBasicLayer::onTouchCancelled( Touch *touch, Event *unused_event )
{

}

void CHrBasicLayer::onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event )
{

}

void CHrBasicLayer::onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event )
{

}

void CHrBasicLayer::onTouchesEnded( const std::vector<Touch*>& touches, Event *unused_event )
{

}

void CHrBasicLayer::onTouchesCancelled( const std::vector<Touch*>&touches, Event *unused_event )
{

}
