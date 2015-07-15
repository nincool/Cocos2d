#pragma once

#include "HrCycleScrollView.h"
using namespace HrFish;
using namespace cocos2d;
USING_NS_CC_EXT;

class CHrTempCell : public CHrCycleCell
{
public:
	static CHrTempCell* create()
	{
		CHrTempCell* pRet = new CHrTempCell();
		if (pRet && pRet->initwith())
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pRet);
		}
		return pRet;
	}
	bool initwith()
	{
		if (CHrCycleCell::init())
		{
			label = CCLabelTTF::create();
			label->setFontSize(80);
			label->setAnchorPoint(ccp(0.5, 0.5));
			label->setPosition(ccp(0, 200));

			//this->setContentSize(CCSizeMake(160, 320));
			this->addChild(label, 2);

			return true;
		}
		return false;

	}

	void GetSelected(){

	}
	void UpdateWithIndex(unsigned int index)
	{
		m_nIndex = index;
		label->setString(CCString::createWithFormat("%d", index)->getCString());
		auto sprTest = Sprite::create("roomname.png");
		addChild(sprTest);
		sprTest->setPosition(0, 0);
		sprTest->setTag(1);
	}

	virtual Size GetCellSize() override 
	{
		return Size(400, 400);
	}

	virtual void SetContentScale(float fScale)
	{
		auto node = getChildByTag(1);
		node->setScale(fScale);
	}
	virtual void SetContentColor(Color3B color)
	{
		auto node = getChildByTag(1);
		node->setColor(color);
	}
private:
	LabelTTF* label;
};

