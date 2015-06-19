#ifndef _EPOLLTHREAD_H_
#define _EPOLLTHREAD_H_

#include "../../HrCommon/HrMacros.h"
#include "TCPSocket.h"
#include "HrThread.h"
#include "MsgQueue.h"
#include <vector>

class CEpollThread : public CHrThread
{
public:
	CEpollThread();
	~CEpollThread();

	enum _SOCKET_STATUS_
	{
		STATUS_UNCONNECTED,
		STATUS_CONNECTED,
		STATUS_CLOSED,
	};
public:
	bool InitEpollThread(const char* pIP, int nPort);
	void InitMsgQueue(MsgQueue* pGetQueue, MsgQueue* pSendQueue);

	_SOCKET_STATUS_ GetSocketStatus()
	{
		return m_socketStatus;
	};

	void CloseSocket();
public:
	virtual int Run() override;

private:
	void ReadDataOnce();


	//子线程调用函数
	void OnDisconnect();
private:
	CGameSocket* m_pTcpSocket;
	_SOCKET_STATUS_ m_socketStatus;
	
	MsgQueue* m_pGetQueue;
	MsgQueue* m_pSendQueue;

	char* m_pGetQueueBuffer;
};



#endif // !_EPOLLTHREAD_H_


