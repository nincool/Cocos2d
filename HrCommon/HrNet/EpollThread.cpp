#include "EpollThread.h"
#include <iostream>


USING_NS_CC;

CEpollThread::CEpollThread()
{
	m_pTcpSocket = new CGameSocket();
	m_pGetQueueBuffer = nullptr;

	m_socketStatus = STATUS_UNCONNECTED;
}

CEpollThread::~CEpollThread()
{
	Stop();

	delete m_pTcpSocket;
	m_pTcpSocket = nullptr;

	delete m_pGetQueueBuffer;
	m_pGetQueueBuffer = nullptr;
}


bool CEpollThread::InitEpollThread(const char* pIP, int nPort)
{
	bool bRetVal = m_pTcpSocket->Create(pIP, nPort);
	if (bRetVal)
	{
		m_socketStatus = STATUS_CONNECTED;
		HRLOG(_HDEBUG, "TCP", "Connected Server Success! IP[%s] PORT[%d]", pIP, nPort);
	}
	else
	{
		HRLOG(_HDEBUG, "TCP", "Connected Server Failed! IP[%s] PORT[%d]", pIP, nPort);
	}
	
	return bRetVal;
}

void CEpollThread::InitMsgQueue(MsgQueue* pGetQueue, MsgQueue* pSendQueue)
{
	m_pGetQueue = pGetQueue;
	m_pSendQueue = pSendQueue;

	m_pGetQueueBuffer = new char[m_pSendQueue->max_msg_len];
}

void CEpollThread::CloseSocket()
{

	m_pTcpSocket->Destroy();
}

int CEpollThread::Run()
{
	//Socket �������쳣
	if (!m_pTcpSocket->Check())
	{
		OnDisconnect();
		m_stopFlag = TO_STOP;

		return 0;
	}

	if (m_pTcpSocket == nullptr)
	{
		return 0;
	}

	//��һ������
	ReadDataOnce();
	//д10������
	for (int i = 0; i < 10; ++i)
	{
		int nDequeueLen = m_pSendQueue->DeQueue(m_pGetQueueBuffer, m_pSendQueue->max_msg_len, 0);
		if (nDequeueLen > 0)
		{
			m_pTcpSocket->SendMsg(m_pGetQueueBuffer, nDequeueLen);
		}
		else
		{
			break;
		}
	}
	//��������
	m_pTcpSocket->Flush();

	return 1;
}

void CEpollThread::ReadDataOnce()
{
	//16 * 1024
	char szBuffer[_MAX_MSGSIZE] = { 0 };
	int nSize = sizeof(szBuffer);
	char* pBufMsg = szBuffer;
	if (m_pTcpSocket == nullptr)
	{
		return;
	}
	if (!m_pTcpSocket->ReceiveMsg(pBufMsg, nSize))
	{
		return;
	}

	//while (true)
	{
		MsgHead* pReceiveMsg = (MsgHead*)pBufMsg;
		int nMsgBufLen = pReceiveMsg->nLen;
		if (nMsgBufLen > nSize || nMsgBufLen <= 0)
		{
			return;
		}
		//���
		m_pGetQueue->EnQueue(pBufMsg, nSize);
	}
}

void CEpollThread::OnDisconnect()
{
	//����һ�����̵߳��ú���
	HRLOG(_HDEBUG, "TCP", "OnDisconnect!");
	//��ʱ����������ĵط�Ӧ��û�о�����ʱ�� 
	m_socketStatus = STATUS_CLOSED;
}
