//////////////////////////////////////////////////////////////////////////////
// Debug handler for new & delete to get more information out of our memory allocation

#ifndef __DEBUGNEW_H__
#define __DEBUGNEW_H__

#include "HrNew.h"

inline void* operator new(size_t size, const char* file, int line)
{
	void* pRetMemory = nullptr;
	if (size > 0)
	{
		pRetMemory = HrPool::CHrNew::New( size, file, line );
	}

	return pRetMemory;
}
//no matching operator delete found
inline void operator delete (void* p, const char* file, int line)
{
	//上面的那个New 有异常
}

template < typename T >
void HrDelete(T* pMemory, const char* file, int line)
{
	//1.调用析构函数
	pMemory->~T();
	//2.回收内存
	HrPool::CHrNew::Delete( pMemory );
}

#define INIT_HR_NEW_POOL(p) HrPool::CHrNew::m_s_pPoolManager = p

#define INHERIT_HR_NEW :public HrPool::CHrPoolListener

// Use this macro in the place of "new"  
#define HR_NEW(type) new(__FILE__, __LINE__)(type)()
// Use this macro in the place of "new Type(Param1)"  
#define HR_NEW1(type, param1) new(__FILE__, __LINE__)(type)(param1)
// Use this macro in the place of "new Type(Param1, Param2)"
#define HR_NEW2(type, param1, param2) new(__FILE__, __LINE__)(type)(param1, param2)

#define HR_DELETE(p) if (p != nullptr) HrDelete(p, __FILE__, __LINE__); p = nullptr

#endif //__DEBUGNEW_H__


