#include "HrThread.h"
#include <thread>


CHrThread::CHrThread()
{
	m_status = STATUS_UNSTART;
	m_stopFlag = TO_STOP;
}


CHrThread::~CHrThread()
{
	if ((m_status == STATUS_RUNNING))
	{
		//还在运行状态的线程必须先停止
		Stop();

		//子线程不能主动调用Jion！！！
		t.join();

	}
	else if (m_status == STATUS_STOPPED)
	{
		//子线程不能主动调用Jion！！！
		t.join();
	}
}

void CHrThread::Start()
{
	//设置结束标记
	m_stopFlag = NO_STOP;
	t = std::thread(&CHrThread::ThreadMain, this, this);
	//设置线程状态
	m_status = STATUS_RUNNING;  
}

bool CHrThread::Stop()
{
	int nTryCounts = 0;

	//设置结束标记为将要结束，在线程中读取并且返回
	m_stopFlag = TO_STOP;
	//如果线程根本没有开启，那么就直接返回
	if (m_status == STATUS_UNSTART)
	{
		return true;
	}
	//在Stop中轮训等待线程结束
	while (true)
	{
		if (m_status == STATUS_STOPPED)
		{
			return true;;
		}
		//这里做一个校验吧 万一碰上了死锁就悲剧了
		++nTryCounts;
	}
}

void CHrThread::ThreadMain(CHrThread* pThread)
{
	while (true)
	{
		if (m_stopFlag == TO_STOP)
		{
			m_status = STATUS_STOPPED;
			return;
		}

		pThread->Run();
	}

}
