#ifndef _HR_NETMANAGER_H_
#define _HR_NETMANAGER_H_

#include "MsgQueue.h"


class CEpollThread;

class CHrNetManager
{
public:
	CHrNetManager();
	~CHrNetManager();

public:
	//��ʼ��Socket��������Socket 128 * 2048
	bool InitNetManager(const char* pIP, int nPort, int nMsgQueueSize = 64, int nMsgQueueLen = 2048);

	/**
	 *	@Comment: �������� [6/6/2015 By Hr]
	 *	@Param: pMsg �������� nLen����s
	*/
	void SendNetMessage(char* pMsg, int nLen);
	/**
	 *	@Comment: ȡ����Ϣ [6/6/2015 By Hr]
	*/
	void GetNetMessage();

	/**
	 *	@Comment: ��Ϣ������ [6/6/2015 By Hr]
	*/
	virtual void OnNetMessage(char* pMsg, unsigned int nLen) = 0;

	void CloseSocket();

	bool IsSocketConnected();
private:
	void ResetNetManager();

	virtual void OnDisConnect();
protected:
	CEpollThread* m_pEpollThread;
	MsgQueue* m_pMsgGetQueue;
	MsgQueue* m_pMsgSendQueue;

	char m_szGetBuffer[2048];


	bool m_bOnDisConnected;
};



#endif // !_HR_NETMANAGER_H_

