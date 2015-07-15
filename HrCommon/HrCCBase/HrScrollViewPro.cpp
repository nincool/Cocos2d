#include "HrScrollViewPro.h"

using namespace HrFish;
USING_NS_CC;
CHrScrollViewPro::CHrScrollViewPro()
{
}


CHrScrollViewPro::~CHrScrollViewPro()
{
}

void CHrScrollViewPro::onTouchEnded(Touch *touch, Event *event)
{
	if (!this->isVisible())
	{
		return;
	}

	auto touchIter = std::find(_touches.begin(), _touches.end(), touch);

	if (touchIter != _touches.end())
	{
		if (_touches.size() == 1 && _touchMoved)
		{
			relocateContainer();
			
			Adjust();
		}
		_touches.erase(touchIter);
	}

	//没有touch时，需要设置状态  
	if (_touches.size() == 0)
	{
		_dragging = false;
		_touchMoved = false;
	}
}

CHrScrollViewPro* HrFish::CHrScrollViewPro::Create(std::vector<Node*>& background, std::vector<CHrCycleCell*>& cycleCell, Size viewSize, _Direction_ direction /*= CycleDirectionHorizontal */)
{
	CHrScrollViewPro* pRet = new CHrScrollViewPro();
	if (pRet && pRet->InitWithViewSize(background, cycleCell, viewSize, direction))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void HrFish::CHrScrollViewPro::Adjust()
{
	if (m_direction == CycleDirectionHorizontal)
	{
		//当_container的坐标为(0,0)时显示区域中心点相对_container坐标
		Vec2 vCenterPos = Vec2(m_backgroundNodeSize.width / 2, 0);
		Vec2 vCenterWorld = convertToWorldSpace(vCenterPos);
		Vec2 vContainPos = _container->convertToNodeSpace(vCenterWorld);
		for (int i = 0; i < 3; ++i)
		{
			Node* pNode = _container->getChildByTag(i);
			for (int j = 0; j < m_nodeCount; ++j)
			{
				CHrCycleCell* pCell = static_cast<CHrCycleCell*>(pNode->getChildByTag(j));
				//把左下角的坐标转换成世界坐标
				Vec2 vNodeWorldPos = pCell->convertToWorldSpace(Vec2(0, 0));
				Size cellSize = pCell->GetCellSize();
				if ((vNodeWorldPos.x - cellSize.width/2 <= vCenterWorld.x) && (vCenterWorld.x <= vNodeWorldPos.x + cellSize.width/2))
				{
					float fPosGap = vCenterWorld.x - vNodeWorldPos.x;
					Vec2 vCurOffset = getContentOffset();
					MyContentOffsetInDuration(Vec2(fPosGap, 0) + vCurOffset, 0.2f);
					
					return;
				}
			}
		}
	}
}

void HrFish::CHrScrollViewPro::MyContentOffsetInDuration(Vec2 offset, float dt)
{
	auto acSeq = Sequence::create(MoveTo::create(dt, offset), CallFuncN::create(CC_CALLBACK_1(CHrScrollViewPro::MyStopContentOffsetInDuration, this)), nullptr);
	_container->runAction(acSeq);
	this->schedule(CC_SCHEDULE_SELECTOR(CHrScrollViewPro::MyPerformedAnimatiedScroll));
}

void HrFish::CHrScrollViewPro::MyStopContentOffsetInDuration(Node* pNode)
{
	this->unschedule(CC_SCHEDULE_SELECTOR(CHrScrollViewPro::MyPerformedAnimatiedScroll));
	relocateContainer();
}

void HrFish::CHrScrollViewPro::MyPerformedAnimatiedScroll(float dt)
{
	if (_dragging)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(CHrScrollViewPro::MyPerformedAnimatiedScroll));
		return;
	}

	if (_delegate != nullptr)
	{
		_delegate->scrollViewDidScroll(this);
	}
}

void HrFish::CHrScrollViewPro::ScrollViewScrolling()
{
	if (m_direction == CycleDirectionHorizontal)
	{
		//当_container的坐标为(0,0)时显示区域中心点相对_container坐标
		Vec2 vCenterPos = Vec2(m_backgroundNodeSize.width / 2, 0);
		Vec2 vCenterWorld = convertToWorldSpace(vCenterPos);
		Vec2 vContainPos = _container->convertToNodeSpace(vCenterWorld);
		for (int i = 0; i < 3; ++i)
		{
			Node* pNode = _container->getChildByTag(i);
			for (int j = 0; j < m_nodeCount; ++j)
			{
				CHrCycleCell* pCell = static_cast<CHrCycleCell*>(pNode->getChildByTag(j));
				//把左下角的坐标转换成世界坐标
				Vec2 vNodeWorldPos = pCell->convertToWorldSpace(Vec2(0, 0));
				Size cellSize = pCell->GetCellSize();
				//当前Cell中心点的世界坐标
				Vec2 vCellCenterPos = vNodeWorldPos;
				float fAbsGap = fabsf(vCellCenterPos.x - vCenterWorld.x);
				if (0 <= fAbsGap && fAbsGap <= cellSize.width / 2)
				{
					float fScale = fabsf((fAbsGap - cellSize.width / 2) / 100.0f) * 0.2 + 1;

					pCell->SetContentScale(fScale);
				}
				else
				{
					pCell->SetContentScale(1);
				}
				if (0 <= fAbsGap && fAbsGap <= cellSize.width / 4)
				{
					pCell->SetContentColor(Color3B(255, 255, 255));
				}
				else
				{
					pCell->SetContentColor(Color3B(100, 100, 100));
				}
			}
		}
	}
}

void HrFish::CHrScrollViewPro::onEnterTransitionDidFinish()
{
	CHrCycleScrollView::onEnterTransitionDidFinish();
	Adjust();
}
