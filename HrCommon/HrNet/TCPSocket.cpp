#include "TCPSocket.h"
#include "../../HrCommon/HrLog/HrLog.h"

CGameSocket::CGameSocket()
{
	// ��ʼ��
	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));
}

void CGameSocket::closeSocket()
{
#ifdef WIN32
	closesocket(m_sockClient);
	WSACleanup();
#elif defined OSX
    shutdown(m_sockClient, 2);
#else
	close(m_sockClient);
#endif
}

bool CGameSocket::Create(const char* pszServerIP, int nServerPort, int nBlockSec, bool bKeepAlive /*= FALSE*/)
{
	// ������
	if (pszServerIP == 0 || strlen(pszServerIP) > 15) {
		return false;
	}

#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if (ret != 0) {
		CHrLog::Instance().Log(_HERROR, "TCP", "WSAStartup Error!");
		return false;
	}
#endif

	// �������׽���
	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sockClient == INVALID_SOCKET) {
		closeSocket();
		CHrLog::Instance().Log(_HERROR, "TCP", "INVALID_SOCKET Error!");
		return false;
	}

	// ����SOCKETΪKEEPALIVE
	if (bKeepAlive)
	{
		int		optval = 1;
		if (setsockopt(m_sockClient, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)))
		{
			closeSocket();
			CHrLog::Instance().Log(_HERROR, "TCP", "setsockopt Error!");
			return false;
		}
	}

#ifdef WIN32
	DWORD nMode = 1;
	int nRes = ioctlsocket(m_sockClient, FIONBIO, &nMode);
	if (nRes == SOCKET_ERROR) {
		closeSocket();
		CHrLog::Instance().Log(_HERROR, "TCP", "ioctlsocket Error!");
		return false;
	}
#else
	// ����Ϊ��������ʽ
	fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
#endif

	unsigned long serveraddr = inet_addr(pszServerIP);
	if (serveraddr == INADDR_NONE)	// ���IP��ַ��ʽ����
	{
		closeSocket();
		CHrLog::Instance().Log(_HERROR, "TCP", "IP��ַ��ʽ���� Error!");
		return false;
	}

	sockaddr_in	addr_in;
	memset((void *)&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nServerPort);
	addr_in.sin_addr.s_addr = serveraddr;

	if (connect(m_sockClient, (sockaddr *)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) {
		if (hasError()) {
			closeSocket();
			return false;
		}
		else	// WSAWOLDBLOCK
		{
			timeval timeout;
			timeout.tv_sec = nBlockSec;
			timeout.tv_usec = 0;
			fd_set writeset, exceptset;
			FD_ZERO(&writeset);
			FD_ZERO(&exceptset);
			FD_SET(m_sockClient, &writeset);
			FD_SET(m_sockClient, &exceptset);

			int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
			if (ret == 0 || ret < 0) {
				closeSocket();
				CHrLog::Instance().Log(_HERROR, "TCP", "select Error!");
				return false;
			}
			else	// ret > 0
			{
				ret = FD_ISSET(m_sockClient, &exceptset);
				if (ret)		// or (!FD_ISSET(m_sockClient, &writeset)
				{
					closeSocket();
					CHrLog::Instance().Log(_HERROR, "TCP", "FD_ISSET Error!");
					return false;
				}
			}
		}
	}

	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;

	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 500;
	setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

	return true;
}

bool CGameSocket::SendMsg(void* pBuf, int nSize)
{
	if (pBuf == 0 || nSize <= 0) {
		return false;
	}

	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	// ���ͨѶ��Ϣ������
	int packsize = 0;
	packsize = nSize;

	// ���BUF���
	if (m_nOutbufLen + nSize > OUTBUFSIZE) {
		// ��������OUTBUF�е����ݣ������OUTBUF��
		Flush();
		if (m_nOutbufLen + nSize > OUTBUFSIZE) {
			// ������
			Destroy();
			return false;
		}
	}
	// ������ӵ�BUFβ
	memcpy(m_bufOutput + m_nOutbufLen, pBuf, nSize);
	m_nOutbufLen += nSize;
	return true;
}

bool CGameSocket::ReceiveMsg(void* pBuf, int& nSize)
{
	//������
	if (pBuf == NULL || nSize <= 0) {
		return false;
	}

	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	// ����Ƿ���һ����Ϣ(С��4���޷���ȡ����Ϣ����) Modify By Hr ->4
	if (m_nInbufLen < 4) {
		//  ���û������ɹ�  ����   ���û��������ֱ�ӷ���
		if (!recvFromSock() || m_nInbufLen < 4) {		// ���m_nInbufLen������
			return false;
		}
	}

	// ����Ҫ��������Ϣ�Ĵ�С��һ����Ϣ����СΪ������Ϣ�ĵ�һ��16�ֽڣ�����Ϊ���λ�����������Ҫ�ֿ�����
	int nPackSize = (*(int*)m_bufInput) + 4;//Э�������С������ǰ���4���ֽ�

	// �����Ϣ���ߴ���� �ݶ����16k
	if (nPackSize <= 0 || nPackSize > _MAX_MSGSIZE) {
		m_nInbufLen = 0;		// ֱ�����INBUF
		m_nInbufStart = 0;
		CHrLog::Instance().Log(_HERROR, "TCP", "Msg Too Length!!!!");
		return false;
	}

	// �����Ϣ�Ƿ�����(�����Ҫ��������Ϣ���ڴ�ʱ���������ݳ��ȣ���Ҫ�ٴ��������ʣ������)
	if (nPackSize > m_nInbufLen) {
		// ���û������ɹ�   ����    ��Ȼ�޷���ȡ�����������ݰ�  �򷵻أ�ֱ��ȡ��������
		if (!recvFromSock() || nPackSize > m_nInbufLen) {	// ���m_nInbufLen�Ѹ���
			return false;
		}
	}

	memcpy(pBuf, m_bufInput, m_nInbufLen);
	nSize = m_nInbufLen;

	// ���¼��㻷�λ�����ͷ��λ��
	m_nInbufStart = 0;
	m_nInbufLen = 0;

	return	true;
}

bool CGameSocket::hasError()
{
#ifdef WIN32
	int err = WSAGetLastError();
	if (err != WSAEWOULDBLOCK) {
#else
	int err = errno;
	if (err != EINPROGRESS && err != EAGAIN) {
#endif
		return true;
	}

	return false;
	}

// �������ж�ȡ�����ܶ�����ݣ�ʵ����������������ݵĵط�
bool CGameSocket::recvFromSock(void)
{
	if (m_nInbufLen >= INBUFSIZE || m_sockClient == INVALID_SOCKET) {
		return false;
	}

	//Modify By Hr ���յ�һ������
	int nSaveLen = INBUFSIZE - m_nInbufLen;
	m_nInbufStart = m_nInbufLen;
	int nSavePos = m_nInbufStart;
	int nReceiveLen = recv(m_sockClient, m_bufInput + m_nInbufStart, nSaveLen, 0);

	if (nReceiveLen > 0)
	{
		// �н��յ�����
		m_nInbufLen += nReceiveLen;

		if (m_nInbufLen > INBUFSIZE) 
		{
			return false;
		}

		// ���յڶ�������(һ�ν���û����ɣ����յڶ�������)
		if (m_nInbufLen < INBUFSIZE)
		{
			nSaveLen = INBUFSIZE - m_nInbufLen;
			m_nInbufStart = m_nInbufLen;
			nSavePos = m_nInbufStart;
			nReceiveLen = recv(m_sockClient, m_bufInput + m_nInbufStart, nSaveLen, 0);
			if (nReceiveLen > 0)
			{
				m_nInbufLen += nReceiveLen;
				if (m_nInbufLen > INBUFSIZE)
				{
					return false;
				}
			}
			else if (nReceiveLen == 0)
			{
				Destroy();
				return false;
			}
			else
			{
				// �����ѶϿ����ߴ��󣨰���������
				if (hasError()) {
					Destroy();
					return false;
				}
			}
		}
	}
	else if (nReceiveLen == 0)
	{
		Destroy();
		return false;
	}
	else {
		// �����ѶϿ����ߴ��󣨰���������
		if (hasError()) {
			Destroy();
			return false;
		}
	}

	return true;
}

bool CGameSocket::Flush(void)		//? ��� OUTBUF > SENDBUF ����Ҫ���SEND����
{
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	if (m_nOutbufLen <= 0) {
		return true;
	}

	// ����һ������
	int	outsize;
	outsize = send(m_sockClient, m_bufOutput, m_nOutbufLen, 0);
	if (outsize > 0) {
		// ɾ���ѷ��͵Ĳ���
		if (m_nOutbufLen - outsize > 0) {
			memcpy(m_bufOutput, m_bufOutput + outsize, m_nOutbufLen - outsize);
		}

		m_nOutbufLen -= outsize;

		if (m_nOutbufLen < 0) {
			return false;
		}
	}
	else {
		if (hasError()) {
			Destroy();
			return false;
		}
	}

	return true;
}

bool CGameSocket::Check(void)
{
	// ���״̬
	if (m_sockClient == INVALID_SOCKET) {
		return false;
	}

	char buf[1];
	int	ret = recv(m_sockClient, buf, 1, MSG_PEEK);
	if (ret == 0) {
		Destroy();
		return false;
	}
	else if (ret < 0) {
		if (hasError()) {
			Destroy();
			return false;
		}
		else {	// ����
			return true;
		}
	}
	else {	// ������
		return true;
	}

	return true;
}

void CGameSocket::Destroy(void)
{
	// �ر�
	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 500;
	int ret = setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

	closeSocket();

	m_sockClient = INVALID_SOCKET;
	m_nInbufLen = 0;
	m_nInbufStart = 0;
	m_nOutbufLen = 0;

	memset(m_bufOutput, 0, sizeof(m_bufOutput));
	memset(m_bufInput, 0, sizeof(m_bufInput));
}
