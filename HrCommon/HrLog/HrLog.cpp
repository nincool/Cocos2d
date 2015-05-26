#include "HrLog.h"
#include <string>
#include <fstream>
#include "cocos2d.h"

CHrLog CHrLog::m_s_instance;

using namespace std;
USING_NS_CC;

CHrLog::CHrLog(void)
{
	memset(&m_stLogConf, 0, sizeof(HrLogConf));
	m_stLogConf.nFileFlag = _HLOG_CONSOLE | _HLOG_FILE;					//д�����̨ д���ļ�
	m_stLogConf.nFormatFlag = _HLOG_DATE | _HLOG_TIME | _HLOG_LEVEL | _HLOG_MODULE;	//���ں�ģ��
	m_stLogConf.nLevelFlag = _HERROR;
}

CHrLog::~CHrLog(void)
{
}

CHrLog& CHrLog::Instance()
{
	return m_s_instance;
}

void CHrLog::LogInit( HrLogConf& stLogConf )
{
	memcpy(&m_stLogConf, &stLogConf, sizeof(m_stLogConf));
	if (m_stLogConf.nFileFlag & _HLOG_CONSOLE)
	{
	}
	m_strLogFileName = stLogConf.strLogFileName;
	string strContent = StringUtils::format("Log Start! Log File:[%s]", stLogConf.strLogFileName.c_str());
	Log(_HERROR, "HLOG", strContent.c_str());
}

void CHrLog::GetFileName()
{
	bool bNeedCreateNew = false;

	//���ȿ��µ�ǰ�Ƿ��һ�ι���log�ļ� 
	if (m_strLogFileNameWithDate.length() > 0 && m_strLogFullPath.length() > 0)
	{
		return;
	}

	MakeFileName();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	string strWriteablePath = FileUtils::getInstance()->getWritablePath();
#elif ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )	
	string strWriteablePath = "E:\\Workspace\\HrProjects\\Log\\";
#endif
	m_strLogFullPath = strWriteablePath + m_strLogFileNameWithDate;
}


void CHrLog::MakeFileName()
{
	char szTimeStarmp[HR_LABELBUFF_LEN];
	memset(szTimeStarmp, 0, sizeof(szTimeStarmp));
	MakeDateStarmp(szTimeStarmp, HR_LABELBUFF_LEN, '-');
	m_strLogFileNameWithDate = StringUtils::format("%s%s", m_strLogFileName.c_str(), szTimeStarmp);
}

void CHrLog::MakeDateStarmp(char* pDateBuf, int nBufLen, char cSpace)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	
	struct cc_timeval now;   
	CCTime::gettimeofdayCocos2d(&now, NULL);   
	struct tm *tm;  
	tm = localtime(&now.tv_sec);  
	int year = tm->tm_year + 1900;  
	int month = tm->tm_mon + 1;  
	int day = tm->tm_mday;  
	int hour=tm->tm_hour;  
	int minute=tm->tm_min;  
	int second=tm->tm_sec;  
	long millSecond=now.tv_sec * 1000 + now.tv_usec / 1000;

	if (cSpace == '-')
		sprintf(pDateBuf, "%d-%02d-%02d", year, month, day);
	else
		sprintf(pDateBuf, "%d/%02d/%02d", year, month, day);
#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;

	if (cSpace == '-')
		sprintf(pDateBuf, "%d-%02d-%02d", year, month, day);
	else
		sprintf(pDateBuf, "%d/%02d/%02d", year, month, day);

#endif
	
}

void CHrLog::MakeTimeStarmp( char* pTimeBuf, int nBufLen )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	struct cc_timeval now;   
	CCTime::gettimeofdayCocos2d(&now, NULL);   
	struct tm *tm;  
	tm = localtime(&now.tv_sec);  
	int year = tm->tm_year + 1900;  
	int month = tm->tm_mon + 1;  
	int day = tm->tm_mday;  
	int hour=tm->tm_hour;  
	int minute=tm->tm_min;  
	int second=tm->tm_sec;  
	long millSecond=now.tv_sec * 1000 + now.tv_usec / 1000;

	sprintf(pTimeBuf, "%d:%02d:%02d", hour, minute, second);

#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;

	sprintf(pTimeBuf, "%d:%02d:%02d", hour, minute, second);

#endif
}

void CHrLog::MakeFullTimeStarmp(char* pTimeBuf, int nBufLen)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	struct tm *tm;
	tm = localtime(&now.tv_sec);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;
	long millSecond = now.tv_sec * 1000 + now.tv_usec / 1000;

	sprintf(pTimeBuf, "[%d/%02d/%02d %d:%02d:%02d]", year, month, day, hour, minute, second);

#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;

	sprintf(pTimeBuf, "[%d/%02d/%02d %d:%02d:%02d]", year, month, day, hour, minute, second);

#endif
}

void CHrLog::Log( unsigned int nLevel, char* pszModule, const char* pszFormatContent )
{
	char szLogBuff[HR_LOGFILEBUFF_LEN];
	memset(szLogBuff, 0, sizeof(szLogBuff));
	
	//���ȼ���Ƿ��ʼ���� ���û�г�ʼ�� ��ô����Ĭ������
	if (m_stLogConf.nLevelFlag > nLevel)
	{
		return;
	}

	if (strlen(pszFormatContent) > HR_LOGCONTENT_LEN)
	{
		return;
	}

	//����ʱ���
	if (m_stLogConf.nFormatFlag & _HLOG_DATE || m_stLogConf.nFormatFlag & _HLOG_TIME)
	{
		char szTimeLavel[HR_LABELBUFF_LEN];
		memset(szTimeLavel, 0, sizeof(szTimeLavel));

		unsigned int iTimeFlag = m_stLogConf.nFormatFlag & (_HLOG_DATE | _HLOG_TIME);
		switch (iTimeFlag)
		{
		case 1:
			{
				MakeDateStarmp(szTimeLavel, HR_LABELBUFF_LEN);
				break;
			}
		case 2:
			{
				MakeTimeStarmp(szTimeLavel, HR_LABELBUFF_LEN);
				break;
			}
		case 3:
			{
				MakeFullTimeStarmp(szTimeLavel, HR_LABELBUFF_LEN);
				break;
			}
		}
		std::strcat(szLogBuff, szTimeLavel);
	}
	
	//����ģ��ȼ�
	unsigned int ret  = m_stLogConf.nFormatFlag & _HLOG_LEVEL;
	if (m_stLogConf.nFormatFlag & _HLOG_LEVEL)
	{
		char szLevelLabel[HR_LABELBUFF_LEN];
		memset(szLevelLabel, 0, sizeof(szLevelLabel));
		MakeLevelLabel(nLevel, szLevelLabel, HR_LABELBUFF_LEN);
		std::strcat(szLogBuff, szLevelLabel);
	}

	//����ģ���Զ����ǩ
	if (m_stLogConf.nFormatFlag & _HLOG_MODULE)
	{
		char szModuleLabel[HR_LABELBUFF_LEN];
		memset(szModuleLabel, 0, sizeof(szModuleLabel));
		szModuleLabel[0] = '[';
		memcpy(szModuleLabel+1, pszModule, HR_LABELBUFF_LEN-1);
		std::strcat(szLogBuff, szModuleLabel);
		std::strcat(szLogBuff, "] ");
	}

	std::strcat(szLogBuff, pszFormatContent);
	std::strcat(szLogBuff, "\n");

	GetFileName();

	fstream out;
	out.open(m_strLogFullPath, ios::app);
	if (out.is_open())
	{
		out << szLogBuff;
		out.close();
	}

	//�ж��Ƿ�д�����̨
	if (m_stLogConf.nFileFlag & _HLOG_CONSOLE)
	{
		printf("%s", szLogBuff);
		fflush(stdout);
	}
}

void CHrLog::MakeLevelLabel( unsigned int nLevel, char* pszLabel, int nBufLen )
{
	if ( pszLabel )
	{
		switch (nLevel)
		{
		case _HALL:
			{
				memcpy(pszLabel, "[ALL]   ", nBufLen);
				break;
			}
		case _HDEBUG:
			{
				memcpy(pszLabel, "[DEBUG] ", nBufLen);
				break;
			}
		case _HNOTE:
			{
				memcpy(pszLabel, "[DEBUG] ", nBufLen);
				break;
			}
		case _HWARN:
			{
				memcpy(pszLabel, "[WARN]  ", nBufLen);
				break;
			}
		case _HERROR:
			{
				memcpy(pszLabel, "[ERROR] ", nBufLen);
				break;
			}
		}
	}
	
}

