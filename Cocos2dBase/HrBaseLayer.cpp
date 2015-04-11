#include "HrBaseLayer.h"

using namespace HrCCBase;

CHrBaseLayer::CHrBaseLayer()
{
}

CHrBaseLayer::~CHrBaseLayer()
{
}

bool CHrBaseLayer::onTouchBegan( Touch *touch, Event *unused_event )
{
	return false;
}

void CHrBaseLayer::onTouchMoved( Touch *touch, Event *unused_event )
{

}

void CHrBaseLayer::onTouchEnded( Touch *touch, Event *unused_event )
{

}

void CHrBaseLayer::onTouchCancelled( Touch *touch, Event *unused_event )
{

}

void CHrBaseLayer::onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event )
{

}

void CHrBaseLayer::onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event )
{

}

void CHrBaseLayer::onTouchesEnded( const std::vector<Touch*>& touches, Event *unused_event )
{

}

void CHrBaseLayer::onTouchesCancelled( const std::vector<Touch*>&touches, Event *unused_event )
{

}
