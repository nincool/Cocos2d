/************************************************************************
*
* @Comment：单例模式一定要注意不要依赖其他静态对象，或者其他单例 ！！！
*
* @Author: Hr
* @Date: [6/9/2015 By Hr]
*
************************************************************************/  
#ifndef _HR_SINGLETON_H_
#define _HR_SINGLETON_H_

#include <memory>

template <typename T>
class CHrSingleTon
{
public:
	static T* Instance()
	{
		if (!m_pSharePtr)
		{
			m_pSharePtr.reset(new T);
		}
		return m_pSharePtr.get();
	}

private:
	static std::unique_ptr<T> m_pSharePtr;
private:
	~CHrSingleTon();
	CHrSingleTon(const CHrSingleTon&);
	CHrSingleTon& operator=(const CHrSingleTon&);
};

template <typename T>
std::unique_ptr<T> CHrSingleTon<T>::m_pSharePtr;

#endif


