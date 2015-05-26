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


