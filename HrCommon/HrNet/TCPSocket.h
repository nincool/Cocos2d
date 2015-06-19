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

#define _MAX_MSGSIZE 16 * 1024		// 暂定一个消息最大为16k
#define BLOCKSECONDS	30			// INIT函数阻塞时间
#define INBUFSIZE	(64*1024)		//?	具体尺寸根据剖面报告调整  接收数据的缓存
#define OUTBUFSIZE	(10*1024)		//? 具体尺寸根据剖面报告调整。 发送数据的缓存，当不超过8K时，FLUSH只需要SEND一次

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
	bool	recvFromSock(void);		// 从网络中读取尽可能多的数据
	bool    hasError();			// 是否发生错误，注意，异步模式未完成非错误
	void    closeSocket();

	SOCKET	m_sockClient;

	// 发送数据缓冲
	char	m_bufOutput[OUTBUFSIZE];	//? 可优化为指针数组
	int		m_nOutbufLen;

	// 环形缓冲区 ->改为不缓冲的大小
	char	m_bufInput[INBUFSIZE];
	int		m_nInbufLen;                //当前缓冲区的长度
	int		m_nInbufStart;				//该变量为队列起点可用位置，0 - (SIZE-1)
};


#endif // !_TCPSOCKET_H_


