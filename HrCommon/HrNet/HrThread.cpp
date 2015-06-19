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
		//��������״̬���̱߳�����ֹͣ
		Stop();

		//���̲߳�����������Jion������
		t.join();

	}
	else if (m_status == STATUS_STOPPED)
	{
		//���̲߳�����������Jion������
		t.join();
	}
}

void CHrThread::Start()
{
	//���ý������
	m_stopFlag = NO_STOP;
	t = std::thread(&CHrThread::ThreadMain, this, this);
	//�����߳�״̬
	m_status = STATUS_RUNNING;  
}

bool CHrThread::Stop()
{
	int nTryCounts = 0;

	//���ý������Ϊ��Ҫ���������߳��ж�ȡ���ҷ���
	m_stopFlag = TO_STOP;
	//����̸߳���û�п�������ô��ֱ�ӷ���
	if (m_status == STATUS_UNSTART)
	{
		return true;
	}
	//��Stop����ѵ�ȴ��߳̽���
	while (true)
	{
		if (m_status == STATUS_STOPPED)
		{
			return true;;
		}
		//������һ��У��� ��һ�����������ͱ�����
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
