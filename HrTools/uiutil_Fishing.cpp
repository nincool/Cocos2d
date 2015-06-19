#include "uiutil_Fishing.h"

USING_NS_CC;
using namespace std;


string  uiutil::getstr(const char *format,...)
{
	string tmpstr;
	va_list pArgs ;
	va_start (pArgs, format) ;
	char buff[256];
	memset(buff,0,256);
	vsprintf (buff, format, pArgs) ;
	va_end (pArgs) ;
	return string(buff) ;

}

int uiutil::log(char *format,...)
{
	/*
	string canwritepath = CCFileUtils::sharedFileUtils()->getWriteablePath();
	string fullpath = canwritepath  + "mylog.txt";
	string tmpstr;
	va_list pArgs ;
	int cnt = 0;
	va_start (pArgs, format) ;
	FILE *fp = fopen(fullpath.c_str(),"a+");
	if(fp){
		struct tm *t;
		time_t tt;
		time(&tt);
		t=localtime(&tt);
		fprintf(fp,"%4d-%02d-%02d %02d:%02d:%02d  ",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
		cnt =vfprintf (fp,format, pArgs) ;

		fprintf(fp,"\n\r");
		fclose(fp);
	}
	va_end (pArgs) ;
	return  cnt ;
	*/
	return 0;
}
int uiutil::log1(char *format,...)
{
	/*
	string canwritepath = CCFileUtils::sharedFileUtils()->getWriteablePath();
	string fullpath = canwritepath  + "mylog1.txt";
	string tmpstr;
	va_list pArgs ;
	int cnt = 0;
	va_start (pArgs, format) ;
	FILE *fp = fopen(fullpath.c_str(),"a+");
	if(fp){
		struct tm *t;
		time_t tt;
		time(&tt);
		t=localtime(&tt);
		fprintf(fp,"%4d-%02d-%02d %02d:%02d:%02d  ",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
		cnt =vfprintf (fp,format, pArgs) ;

		fprintf(fp,"\n\r");
		fclose(fp);
	}
	va_end (pArgs) ;
	return  cnt ;
	*/
	return 0;

}

int uiutil::log2(char *format,...)
{
	string canWritePath = FileUtils::getInstance()->getWritablePath();
	string fullpath = canWritePath + "mylog3.txt";
	string tmpstr;
	va_list pArgs ;
	int cnt = 0;
	va_start (pArgs, format) ;
	FILE *fp = fopen(fullpath.c_str(),"a+");
	if(fp){
		struct tm *t;
		time_t tt;
		time(&tt);
		t=localtime(&tt);
		fprintf(fp,"%4d-%02d-%02d %02d:%02d:%02d  ",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
		cnt =vfprintf (fp,format, pArgs) ;

		fprintf(fp,"\n\r");
		fclose(fp);
	}
	va_end (pArgs) ;
	return  cnt ;
}



