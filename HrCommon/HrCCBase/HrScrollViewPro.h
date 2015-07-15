#ifndef _HR_SCROLLVIEWPRO_H_
#define _HR_SCROLLVIEWPRO_H_

#include "HrCycleScrollView.h"

namespace HrFish
{
	class CHrScrollViewPro : public CHrCycleScrollView
	{
	public:
		CHrScrollViewPro();
		virtual ~CHrScrollViewPro();

		static CHrScrollViewPro* Create(std::vector<Node*>& background
			, std::vector<CHrCycleCell*>& cycleCell
			, Size viewSize
			, _Direction_ direction = CycleDirectionHorizontal
			);
	public:
		virtual void onTouchEnded(Touch *touch, Event *event) override;
	private:
		void Adjust();
		void MyContentOffsetInDuration(Vec2 offset, float dt);
		void MyStopContentOffsetInDuration(Node* pNode);
		void MyPerformedAnimatiedScroll(float dt);

		virtual void ScrollViewScrolling() override;
		virtual void onEnterTransitionDidFinish() override;
	};
}


#endif

