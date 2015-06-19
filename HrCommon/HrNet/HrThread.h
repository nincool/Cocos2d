#ifndef _HR_THREAD_H_
#define _HR_THREAD_H_
#endif // !_HR_HTREAD_H_

#include <thread>

typedef enum				/*Detach state*/
{
	JOINABLE,
	DETACHED
}DetachStateDef;

typedef enum
{
	NORMAL,
	HIGH
}PriorityDef;

typedef enum
{
	STATUS_UNSTART,
	STATUS_RUNNING,
	STATUS_STOPPED,
}ThreadStatus;

typedef enum
{
	NO_STOP,
	TO_STOP,
}StopFlag;

class CHrThread
{
public:
	CHrThread();
	~CHrThread();

public:
	//start �� stop �����������߳��е���
	void Start();
	bool Stop();
	
	ThreadStatus GetStatus()
	{
		return m_status;
	};

	StopFlag GetStopFlag()
	{
		return m_stopFlag;
	};
protected:
	virtual int Run() = 0;
	
	void ThreadMain(CHrThread* pThread);

	std::thread t;

	ThreadStatus m_status;
	StopFlag m_stopFlag;
};

