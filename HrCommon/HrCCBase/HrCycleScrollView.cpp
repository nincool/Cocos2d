#include "HrCycleScrollView.h"

using namespace HrFish;
using namespace std;
USING_NS_CC;

#define SCROLL_DEACCEL_RATE  0.95f  
#define SCROLL_DEACCEL_DIST  1.0f 

CHrCycleScrollView::CHrCycleScrollView():
	m_backgroundNodeLeft(NULL),
	m_backgroundNodeMiddle(NULL),
	m_backgroundNodeRight(NULL),
	m_lastPoint(Point(0.0f, 0.0f)),
	m_nowPoint(Point(0.0f, 0.0f)),
	m_lastPositionNum(0),
	m_lastPositiveDone(false),
	m_lastNegtiveDone(false),
	m_isTouchDirection(false)
{
}

CHrCycleScrollView::~CHrCycleScrollView()
{
}

CHrCycleScrollView* HrFish::CHrCycleScrollView::Create(std::vector<Node*>& background
	, std::vector<CHrCycleCell*>& cycleCell
	, Size viewSize
	, _Direction_ direction /*= CycleDirectionHorizontal*/)
{
	CHrCycleScrollView* pRet = new CHrCycleScrollView();
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

bool HrFish::CHrCycleScrollView::InitWithViewSize(std::vector<Node*>& background
	, std::vector<CHrCycleCell*>& cycleCell
	, Size viewSize
	, _Direction_ direction /*= CycleDirectionHorizontal*/)
{
	if (Layer::init())
	{
		CCASSERT(background.size() == 3, "failed 1");
		CCASSERT(cycleCell.size() % 3 == 0, "falied 2");
		m_nodeCount = cycleCell.size() / 3;
		m_totalCount = cycleCell.size();

		//initial the background node
		m_backgroundNodeLeft = background[0];
		m_backgroundNodeMiddle = background[1];
		m_backgroundNodeRight = background[2];
		
		if (!this->_container)
		{
			_container = CCLayer::create();
			this->_container->addChild(m_backgroundNodeLeft);
			this->_container->addChild(m_backgroundNodeMiddle);
			this->_container->addChild(m_backgroundNodeRight);
		}
		m_viewSize = viewSize;
		
		//initial the cell in every backNode.  
		for (int i = 0; i < m_nodeCount; ++i)
		{
			CHrCycleCell* pCycleCellLeft = cycleCell[i];
			pCycleCellLeft->setTag(i);
			pCycleCellLeft->UpdateWithIndex(i);
			m_backgroundNodeLeft->addChild(pCycleCellLeft);

			CHrCycleCell* pCycleCellMid = cycleCell[m_nodeCount + i];
			pCycleCellMid->setTag(i);
			pCycleCellMid->UpdateWithIndex(i);
			m_backgroundNodeMiddle->addChild(pCycleCellMid);

			CHrCycleCell* pCycleCellRight = cycleCell[m_nodeCount * 2 + i];
			pCycleCellRight->setTag(i);
			pCycleCellRight->UpdateWithIndex(i);
			m_backgroundNodeRight->addChild(pCycleCellRight);
			if (direction == CycleDirectionHorizontal)
			{
				pCycleCellLeft->setPosition(Vec2(pCycleCellLeft->GetCellSize().width *i, 0));
				pCycleCellMid->setPosition(Vec2(pCycleCellMid->GetCellSize().width *i, 0));
				pCycleCellRight->setPosition(Vec2(pCycleCellRight->GetCellSize().width *i, 0));
			}
			else
			{
				pCycleCellLeft->setPosition(Vec2(0, pCycleCellLeft->GetCellSize().height * i));
				pCycleCellMid->setPosition(Vec2(0, pCycleCellMid->GetCellSize().height * i));
				pCycleCellRight->setPosition(Vec2(0, pCycleCellRight->GetCellSize().height * i));
			}
		}
		if (direction == CycleDirectionHorizontal)
		{
			//计算单个Container的宽度
			float fWidth = 0;
			for (int i = 0; i < m_nodeCount; ++i)
			{
				fWidth += cycleCell[i]->GetCellSize().width;
			}
			m_backgroundNodeSize.width = fWidth;
			float fPerContainerWidth = fWidth;
			m_backgroundNodeLeft->setPosition(Vec2(-fPerContainerWidth, 0.0f));
			m_backgroundNodeMiddle->setPosition(Vec2(0.0f, 0.0f));
			m_backgroundNodeRight->setPosition(Vec2(fPerContainerWidth, 0.0f));
			_direction = ScrollView::Direction::HORIZONTAL;

		}
		else if (direction == CycleDirectionVertical)
		{
			float fHeight = 0;
			for (int i = 0; i < m_nodeCount; ++i)
			{
				fHeight += cycleCell[i]->GetCellSize().height;
			}
			m_backgroundNodeSize.height = fHeight;
			float fPerContainerHeight = fHeight;
			m_backgroundNodeLeft->setPosition(Vec2(0.0f, -fPerContainerHeight));
			m_backgroundNodeMiddle->setPosition(Vec2(0.0f, 0.0f));
			m_backgroundNodeRight->setPosition(Vec2(0.0f, fPerContainerHeight));
			_direction = ScrollView::Direction::VERTICAL;
		}

		//updateCycleCell(true);
		this->setViewSize(m_viewSize);

		setTouchEnabled(true);
		_touches.reserve(EventTouch::MAX_TOUCHES);
		_bounceable = true;
		_clippingToBounds = true;

		_container->setPosition(Vec2(0.0f, 0.0f));

		this->addChild(_container);
		m_direction = direction;
		_delegate = this;
		return true;
	}
	return false;
}

bool HrFish::CHrCycleScrollView::onTouchBegan(Touch *touch, Event *event)
{
	bool result = ScrollView::onTouchBegan(touch, event);
	m_lastPoint = convertToWorldSpace(convertTouchToNodeSpace(touch));
	m_isTouchDirection = true;
	if (_touches.size() > 1)
	{
		return false;
	}
	return result;

}

void HrFish::CHrCycleScrollView::onTouchMoved(Touch *touch, Event *event)
{
	m_nowPoint = convertToWorldSpace(convertTouchToNodeSpace(touch));
	ScrollView::onTouchMoved(touch, event);
}

void HrFish::CHrCycleScrollView::onTouchEnded(Touch *touch, Event *event)
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
			this->schedule(CC_SCHEDULE_SELECTOR(CHrCycleScrollView::deaccelerateScrolling));
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

void HrFish::CHrCycleScrollView::onTouchCancelled(Touch *touch, Event *event)
{
	ScrollView::onTouchCancelled(touch, event);
	m_isTouchDirection = false;
}

void HrFish::CHrCycleScrollView::scrollViewDidScroll(ScrollView* view)
{
	if (m_direction == CycleDirectionHorizontal)
	{
		if (m_isTouchDirection)
		{
			float fGap = m_nowPoint.x - m_lastPoint.x;
			CCLOG("GAP!!!!!!!!!!!!!!! %f", fGap);
			if (fGap >= 0.00001)
			{
				m_moving = Right;
				m_lastPoint = m_nowPoint;
				CCLOG("Set Move Right!!!!!! %f %f", m_nowPoint.x, m_lastPoint.x);
			}
			else if (fGap <= -0.00001)
			{
				m_moving = Left;
				m_lastPoint = m_nowPoint;
				CCLOG("Set Move Left!!!!!! %f %f", m_nowPoint.x, m_lastPoint.x);
			}
			else
			{
				CCLOG("Dir  change not");
			}
		}
		m_nowPositionNum = _container->getPositionX() / m_backgroundNodeSize.width;
	}
	else if (m_direction == CycleDirectionVertical)
	{


		if (m_isTouchDirection)
		{
			if (m_nowPoint.y > m_lastPoint.y)
			{
				m_moving = Up;
				m_lastPoint = m_nowPoint;
			}
			else
			{
				m_moving = Down;
				m_lastPoint = m_nowPoint;
			}

		}

		m_nowPositionNum = _container->getPositionY() / m_backgroundNodeSize.height;
	}

	adjustBackgroundNode();
}

void HrFish::CHrCycleScrollView::scrollViewDidZoom(ScrollView* view)
{

}

void HrFish::CHrCycleScrollView::adjustBackgroundNode()
{
	//正在向右移动  
	//CCLOG("The moving direction is %d pos:%f %f", m_moving, _container->getPosition().x, _container->getPosition().y);
	//CCLOG("The now Num is %f", m_nowPositionNum);
	//CCLOG("The last Num is%d", m_lastPositionNum);
	//CCLOG("MidPos:%f %f", m_backgroundNodeMiddle->getPositionX(), m_backgroundNodeMiddle->getPositionY());
	if (m_direction == CycleDirectionHorizontal)
	{
		if (m_moving == Right)
		{
			if (m_nowPositionNum - m_lastPositionNum > 0.5)
			{
				m_lastPositiveDone = true;
				m_lastPositionNum++;
			}
			if (m_lastPositiveDone)
			{
				m_backgroundNodeRight->setPosition(Vec2(m_backgroundNodeRight->getPositionX() - m_backgroundNodeSize.width * 3, 0));

				Node* temp = m_backgroundNodeRight;
				m_backgroundNodeRight = m_backgroundNodeMiddle;
				m_backgroundNodeMiddle = m_backgroundNodeLeft;
				m_backgroundNodeLeft = temp;
				//CCLOG("Change Right!");
				//updateCycleCell();
				m_lastPositiveDone = false;
			}
		}
		else if (m_moving == Left)
		{
			if (m_lastPositionNum - m_nowPositionNum >= 0.5)
			{
				m_lastNegtiveDone = true;
				m_lastPositionNum--;
			}
			if (m_lastNegtiveDone)
			{
				m_backgroundNodeLeft->setPosition(Vec2(m_backgroundNodeLeft->getPositionX() + m_backgroundNodeSize.width * 3, 0));

				Node* temp = m_backgroundNodeLeft;
				m_backgroundNodeLeft = m_backgroundNodeMiddle;
				m_backgroundNodeMiddle = m_backgroundNodeRight;
				m_backgroundNodeRight = temp;
				//CCLOG("Change Left!");
				//updateCycleCell();
				m_lastNegtiveDone = false;
			}
		}
	}
	else if (m_direction == CycleDirectionVertical)
	{
		if (m_moving == Up)
		{
			if (m_nowPositionNum - m_lastPositionNum > 0.5)
			{
				m_lastPositiveDone = true;
				m_lastPositionNum++;
			}

			if (m_lastPositiveDone)
			{
				m_backgroundNodeRight->setPosition(Vec2(0.0f, m_backgroundNodeRight->getPositionY() - m_backgroundNodeSize.height * 3));
				Node* temp = m_backgroundNodeRight;
				m_backgroundNodeRight = m_backgroundNodeMiddle;
				m_backgroundNodeMiddle = m_backgroundNodeLeft;
				m_backgroundNodeLeft = temp;
				//updateCycleCell();
				m_lastPositiveDone = false;

			}

		}
		else if (m_moving == Down)
		{
			if (m_lastPositionNum - m_nowPositionNum >= 0.5)
			{
				m_lastNegtiveDone = true;
				m_lastPositionNum--;
			}

			if (m_lastNegtiveDone)
			{

				m_backgroundNodeLeft->setPosition(Vec2(0.0f, m_backgroundNodeLeft->getPositionY() + m_backgroundNodeSize.height * 3));
				Node* temp = m_backgroundNodeLeft;
				m_backgroundNodeLeft = m_backgroundNodeMiddle;
				m_backgroundNodeMiddle = m_backgroundNodeRight;
				m_backgroundNodeRight = temp;
				//updateCycleCell();

				m_lastNegtiveDone = false;
			}
		}
	}
}

void HrFish::CHrCycleScrollView::deaccelerateScrolling(float dt)
{
	//如果刚好在帧开始前 又有一个触摸点发生了began，造成了滚动状态，则取消并返回  
	if (_dragging)
	{
		this->unschedule(schedule_selector(CHrCycleScrollView::deaccelerateScrolling));
		return;
	}

	//好玩的东西来咯  

	float newX, newY;
	Point maxInset, minInset;
	_container->setPosition(_container->getPosition() + _scrollDistance);

	if (m_direction == CycleDirectionHorizontal)
	{
		m_nowPositionNum = _container->getPositionX() / m_backgroundNodeSize.width;
	}
	else if (m_direction == CycleDirectionVertical)
	{
		m_nowPositionNum = _container->getPositionY() / m_backgroundNodeSize.height;
	}

	newX = _container->getPosition().x;
	newY = _container->getPosition().y;

	_scrollDistance = _scrollDistance - Vec2(newX - _container->getPosition().x, newY - _container->getPosition().y);
	_scrollDistance = _scrollDistance * SCROLL_DEACCEL_RATE;
	this->setContentOffset(Vec2(newX, newY));

	if ((fabsf(_scrollDistance.x) <= SCROLL_DEACCEL_DIST &&
		fabsf(_scrollDistance.y) <= SCROLL_DEACCEL_DIST))
	{
		this->unschedule(schedule_selector(CHrCycleScrollView::deaccelerateScrolling));
		this->relocateContainer();
	}
}

void HrFish::CHrCycleScrollView::relocateContainer()
{
	Vec2 endPos = findEndPoint();

	if (m_direction == CycleDirectionHorizontal)
	{
		m_nowPositionNum = endPos.x / m_backgroundNodeSize.width;
	}
	else if (m_direction == CycleDirectionVertical)
	{
		m_nowPositionNum = endPos.y / m_backgroundNodeSize.height;
	}
	this->setContentOffset(endPos);
	adjustBackgroundNode();  
}

Point HrFish::CHrCycleScrollView::findEndPoint()
{
	Vec2 endPos = _container->getPosition();
	//终点其实也是Mid的中心点
	//先统一修复下位置试试
	m_lastPositionNum = 0;
	if (m_direction == CycleDirectionHorizontal)
	{
		int nCountNum = endPos.x / m_backgroundNodeSize.width;
		float fPosX = endPos.x - m_backgroundNodeSize.width * nCountNum;
		
		float fPerContainerWidth = m_backgroundNodeSize.width;
		m_backgroundNodeLeft->setPosition(Vec2(-fPerContainerWidth, 0.0f));
		m_backgroundNodeMiddle->setPosition(Vec2(0.0f, 0.0f));
		m_backgroundNodeRight->setPosition(Vec2(fPerContainerWidth, 0.0f));

		return Point(fPosX, endPos.y);
	}
	else
	{
		int nCountNum = endPos.y / m_backgroundNodeSize.height;
		float fPosY = endPos.y - m_backgroundNodeSize.height * nCountNum;
		
		float fPerContainerHeight = m_backgroundNodeSize.height;
		m_backgroundNodeLeft->setPosition(Vec2(0.0f, -fPerContainerHeight));
		m_backgroundNodeMiddle->setPosition(Vec2(0.0f, 0.0f));
		m_backgroundNodeRight->setPosition(Vec2(0.0f, fPerContainerHeight));
		return Point(endPos.x, fPosY);
	}
	

	return endPos;
}

void HrFish::CHrCycleScrollView::updateCycleCell(bool bothSide /*= false*/)
{
	//if (m_moving == Right || bothSide || m_moving == Up)
	//{
	//	CHrCycleCell* cycleCell = static_cast<CHrCycleCell*>(m_backgroundNodeMiddle->getChildByTag(0));
	//	unsigned int index = cycleCell->GetIndex();

	//	index--;
	//	for (int i = m_nodeCount - 1; i >= 0; i--)
	//	{
	//		if (index == 0)
	//		{
	//			index = m_totalCount;
	//		}
	//		((CHrCycleCell*)m_backgroundNodeLeft->getChildByTag(i))->UpdateWithIndex(index);
	//		index--;
	//	}

	//}
	//if (m_moving == Left || bothSide || m_moving == Down)
	//{
	//	CHrCycleCell* cycleCell = static_cast<CHrCycleCell*>(m_backgroundNodeMiddle->getChildByTag(m_nodeCount - 1));
	//	unsigned int index = cycleCell->GetIndex();
	//	CCLOG("The left index is %d", index);
	//	CCLOG("The total count is %d", m_totalCount);
	//	index++;
	//	for (int i = 0; i < m_nodeCount; i++)
	//	{
	//		if (index > m_totalCount)
	//		{
	//			index = 1;

	//			CCLOG("Beyond the index");
	//		}
	//		((CHrCycleCell*)m_backgroundNodeRight->getChildByTag(i))->UpdateWithIndex(index);
	//		index++;
	//	}
	//}
}
