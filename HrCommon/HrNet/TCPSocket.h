#ifndef _TCPSOCKET_H_
#define _TCPSOCKET_H_

#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

#endif

#ifndef CHECKF
#define CHECKF(x) 
//do \
	//	{ \
	//if (!(x)) { \
	//log_msg("CHECKF", #x, __FILE__, __LINE__); \
	//return 0; \
	//		} \
	//	} while (0)
#endif

struct MsgHead
{
	int nLen;
};

#define _MAX_MSGSIZE 16 * 1024		// �ݶ�һ����Ϣ���Ϊ16k
#define BLOCKSECONDS	30			// INIT��������ʱ��
#define INBUFSIZE	(64*1024)		//?	����ߴ�������汨�����  �������ݵĻ���
#define OUTBUFSIZE	(10*1024)		//? ����ߴ�������汨������� �������ݵĻ��棬��������8Kʱ��FLUSHֻ��ҪSENDһ��

class CGameSocket {
public:
	CGameSocket(void);
	bool	Create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
	bool	SendMsg(void* pBuf, int nSize);
	bool	ReceiveMsg(void* pBuf, int& nSize);
	bool	Flush(void);
	bool	Check(void);
	void	Destroy(void);
	SOCKET	GetSocket(void) const { return m_sockClient; }
private:
	bool	recvFromSock(void);		// �������ж�ȡ�����ܶ������
	bool    hasError();			// �Ƿ�������ע�⣬�첽ģʽδ��ɷǴ���
	void    closeSocket();

	SOCKET	m_sockClient;

	// �������ݻ���
	char	m_bufOutput[OUTBUFSIZE];	//? ���Ż�Ϊָ������
	int		m_nOutbufLen;

	// ���λ����� ->��Ϊ������Ĵ�С
	char	m_bufInput[INBUFSIZE];
	int		m_nInbufLen;                //��ǰ�������ĳ���
	int		m_nInbufStart;				//�ñ���Ϊ����������λ�ã�0 - (SIZE-1)
};


#endif // !_TCPSOCKET_H_


