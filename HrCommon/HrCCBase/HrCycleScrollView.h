#ifndef _HR_CYCLESCROLLVIEW_H_
#define _HR_CYCLESCROLLVIEW_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace HrFish
{
	enum _MovingDirection_
	{
		Left = 1,
		Right = 2,
		Up,
		Down
	};

	//The direction that the view allowd to move, the view can't do the both like CCScrollView.  
	enum _Direction_
	{
		CycleDirectionHorizontal = 1,
		CycleDirectionVertical

	};

	class CHrCycleCell : public Node
	{
	public:
		virtual void GetSelected() = 0;
		virtual void UpdateWithIndex(unsigned int index) = 0;
		virtual Size GetCellSize() = 0;
		unsigned int GetIndex(){ return m_nIndex; }

	protected:
		unsigned int m_nIndex;
	};

	class CHrCycleScrollView : public ScrollView, public ScrollViewDelegate
	{
	public:
		CHrCycleScrollView();
		virtual ~CHrCycleScrollView();

	public:
		/*
		The background node is the background that will be show cyclely.
		The nodeCount is the count that every background node can hold the cycleCell.
		The totalCount is the count that how many different data in the cycle cell.Eg...The hour in a day ,can have the 24 totalCount.
		至少要有3个节点
		*/
		static CHrCycleScrollView* Create(std::vector<Node*>& background
			, std::vector<CHrCycleCell*>& cycleCell
			, Size viewSize
			, _Direction_ direction = CycleDirectionHorizontal
			);

		bool InitWithViewSize(std::vector<Node*>& background
			, std::vector<CHrCycleCell*>& cycleCell
			, Size viewSize
			, _Direction_ direction = CycleDirectionHorizontal);

		/*
		TouchDelegate.
		*/
		virtual bool onTouchBegan(Touch *touch, Event *event) override;
		virtual void onTouchMoved(Touch *touch, Event *event) override;
		virtual void onTouchEnded(Touch *touch, Event *event) override;
		virtual void onTouchCancelled(Touch *touch, Event *event) override;
	protected:

		//CCScrollViewDelegate  
		virtual void scrollViewDidScroll(ScrollView* view) override;
		virtual void scrollViewDidZoom(ScrollView* view) override;

		//The delegate must be self, so beyound the class ,anyone can't change the scrollview delegate.  
		void setDelegate(){};


		/*
		we should adjust the backgroundNode's position so that the view will cyclely move.
		*/
		void adjustBackgroundNode();

		/*
		The similar functions with the CCScrollView
		*/
		void deaccelerateScrolling(float dt);

		/*
		we should relocate the view to the position where the offset must be integer to make sure that one cycle cell must be selected
		*/
		void relocateContainer();

		/*
		find the final point where the view should be relocated
		*/
		Point findEndPoint();

		/*
		to change the index of the cycle cell
		*/
		void updateCycleCell(bool bothSide = false);

		//The background node that will show cyclely.  
		Node* m_backgroundNodeLeft;
		Node* m_backgroundNodeMiddle;
		Node* m_backgroundNodeRight;


		Size m_backgroundNodeSize;
		Size m_viewSize;

		//the last touch point   
		Point m_lastPoint;
		//the current touch point , use them to tell the direction that the view is moving.  
		Point m_nowPoint;

		//the current postionNum offset of the container,which tells the view when to adjust the backgroudnode.  
		float m_nowPositionNum;
		//the last postionNum offset of the container,pay attention to the type of them,one is float and one is integer.  
		int m_lastPositionNum;


		//if the backgroundnode has been adjust, the position direction includes right and up.  
		bool m_lastPositiveDone;
		//the same as positive,but the direction includes left and down.   
		bool m_lastNegtiveDone;

		//the direction that the view is moving.  
		_MovingDirection_ m_moving;

		//limit the direction that the view can move  
		_Direction_ m_direction;
		//if the touch can change the direction  
		bool m_isTouchDirection;

		//The total index of the cycle cell  
		//一共有多少个节点
		unsigned int m_totalCount;
		
		//the number of the cycle cell that every background should hold
		//单个视图节点中存放的多少个Cell
		unsigned int m_nodeCount;
	};


}

#endif

