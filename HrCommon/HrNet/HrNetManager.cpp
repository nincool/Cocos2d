#include "HrNetManager.h"
#include "EpollThread.h"


CHrNetManager::CHrNetManager()
{
	m_pEpollThread = nullptr;
	m_pMsgGetQueue = nullptr;
	m_pMsgSendQueue = nullptr;
	m_bOnDisConnected = false;

	memset(m_szGetBuffer, 0, sizeof(m_szGetBuffer));
}

CHrNetManager::~CHrNetManager()
{
	//先结束线程，在析构函数中等待线程结束
	CC_SAFE_DELETE(m_pEpollThread);

	CC_SAFE_DELETE(m_pMsgGetQueue);
	CC_SAFE_DELETE(m_pMsgSendQueue);
}

bool CHrNetManager::InitNetManager(const char* pIP, int nPort, int nMsgQueueSize, int nMsgQueueLen)
{
	m_pMsgGetQueue = new MsgQueue(nMsgQueueSize, nMsgQueueLen);
	m_pMsgSendQueue = new MsgQueue(nMsgQueueSize, nMsgQueueLen);

	m_pEpollThread = new CEpollThread();
	m_pEpollThread->InitMsgQueue(m_pMsgGetQueue, m_pMsgSendQueue);
	//初始化连接线程
	bool bConnected = m_pEpollThread->InitEpollThread(pIP, nPort);
	if (bConnected)
	{
		m_pEpollThread->Start();
	}

	return bConnected;
} 

void CHrNetManager::SendNetMessage(char* pMsg, int nLen)
{
	//加入到发送队列中
	m_pMsgSendQueue->EnQueue(pMsg, nLen);
}

void CHrNetManager::GetNetMessage()
{
	if (m_pEpollThread->GetSocketStatus() == CEpollThread::STATUS_CLOSED)
	{
		if (!m_bOnDisConnected)
		{
			m_bOnDisConnected = true;
			OnDisConnect();
		}
	}

	if (m_pEpollThread->GetSocketStatus() == CEpollThread::STATUS_UNCONNECTED || m_pEpollThread->GetSocketStatus() == CEpollThread::STATUS_CLOSED)
	{
		return;
	}

	while (true)
	{
		memset(m_szGetBuffer, 0, sizeof(m_szGetBuffer));
	    int nLen = m_pMsgGetQueue->DeQueue(m_szGetBuffer, sizeof(m_szGetBuffer), 0);
		if (nLen > 0)
		{
			OnNetMessage(m_szGetBuffer, (unsigned int)nLen);
		}
		else
		{
			break;
		}
	}
}

void CHrNetManager::CloseSocket()
{
	if (m_pEpollThread != nullptr)
		m_pEpollThread->CloseSocket();
}

bool CHrNetManager::IsSocketConnected()
{
	if (m_pEpollThread->GetSocketStatus() == CEpollThread::STATUS_CONNECTED)
	{
		return true;
	}

	return false;
}

void CHrNetManager::ResetNetManager()
{

}

void CHrNetManager::OnDisConnect()
{

}
