//ע��:��ͳһ���߳���,��������ʹ��TADD_START,����Ḳ��.

#ifndef __AUTOTEST_LOG_H__
#define __AUTOTEST_LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
using namespace std;

#define  TLOG_NORMAL       0     //������־, ������ζ���¼(�����ļ�(����)��)
#define  TLOG_FLOW         1     //��ϸ��־(��¼��)
#define  TLOG_FUNC         2     //һ�������־, ����������ù���
#define  TLOG_DETAIL       3     //��ϸ���Լ�¼, �������ʱ����

#define  TLOG_WARNING -100     //һ��澯(���ݴ���)
#define  TLOG_FATAL   -200     //���ظ澯(ϵͳ��Դ����, �������ʧ��)

#define MAX_THREAD_COUNTS 128
#define MAX_SYSTEM_THREAD_COUNTS 32
#define MAX_BUSINESS_NAME_LEN 32
#define MAX_PATH_NAME_LEN 256
#define MAX_LOG_BUFFER_LEN 10240

//ϵͳ��־��
class TLog 
{
public:
    void Release();
public:
    void Start(const char * sAppName, int iLevel, bool bFlag);
    void End();
    void Log(const char * fmt, ...);
	void LogEx(const char * sFileName,int  iFileLine,const char * sFuncName,const char * fmt, ...);//��¼������Ϣ��log
	
    void SetLogLevel(int iLevel);
    inline void SetNowLogLevel(int iLevel)
	{
		m_iNowLogLevel = iLevel;
	}
    void SetLogSize(int iLogSize);
    void SetShowConsole(bool bFlag);
    void SetTrace(bool bFlag);
    void SetTraceInfo(const char* pszInfo);
    int  GetLogLevel()
    {
    	return m_iLogLevel;
    }
    
    int GetNowLogLevel();
    
    
    int  GetLogSize() ;
    FILE *GetLogFile(void);

public: 
	TLog();
	TLog(const TLog& log) { }
    ~TLog();    
    long GetFileSize(char * sFullPathFileName);    
    bool CheckAndBackup(const char *sFullPathFileName , FILE*& fp);
    bool IsExist(const char *sFileName);
	unsigned long int  GetID();
    void GetLevelName(int iLogLevel, char sInfo[]);
    FILE* GetFile();
    void GetCurrentTimeStr(char sTime[]=NULL,size_t iLen=0,const bool bLongFlag=false);
    int  m_iLogLevel;     //�趨����־�ļ���
    char m_sPath[MAX_PATH_NAME_LEN];	
    char m_pszFileName[MAX_PATH_NAME_LEN];
	char m_pszErrorFileName[MAX_PATH_NAME_LEN];//ֻ��¼������־
    int m_iNowLogLevel;
private:
	int GetPID();//��ȡ���̺�
	unsigned long GetTID();//��ȡ�̺߳�
	bool Remove(const char * sFileName);
	bool Rename(const char * srcFileName, const char * desFileName, bool bSameFileSystem);
	bool Mkdir(const char * sPath);
private:
    bool m_bShowConsole;  //�Ƿ�����Ļ��ӡ  
    int  m_iLogSize;      //�趨LOG�ļ����Ĵ�С����λΪM����������˴�С���򱸷��ļ�
    int iPos ;
    char m_sAppName[32];
    int m_iPid;
	bool m_logFlag;//��־�Ƿ���Ч
};

extern "C" TLog* gpSimpleLogInstance;      //����ʵ��

//�Ƿ�ʹ����־,TADD == Thread Add
#ifndef _DEBUG
    #define TIS_DEBUG(x) if(false)
#else
	#define TIS_DEBUG(x) if(true)
#endif

#define STRACE_START(x) gpSimpleLogInstance->IsTrackFlag = (x) 
#define STADD_START(sAppName,iLevel,bFlag) gpSimpleLogInstance->Start(sAppName, iLevel,bFlag)

#define STADD_END() gpSimpleLogInstance->End()
#define STADD_SET_LOG_LEVEL(iLevel) gpSimpleLogInstance->SetLogLevel(iLevel)
#define STADD_SET_LOG_SHOWCONSOLE(isShow) gpSimpleLogInstance->SetShowConsole(isShow)

//�����ӡ��Ϣ��
#define __WHERE_SHORT__ __FILE__,__LINE__,__FUNCTION__
#define __WHEREFORMAT_SHORT__ "[%s:%d][%s]: "

//add by jin.shaohua
#ifdef OS_SUN
#define __FUNCTION__ ""
//sun�����в�֧��##���������������������һ��
#define STADD_ERROR(...) gpSimpleLogInstance->SetNowLogLevel(TLOG_FATAL), gpSimpleLogInstance->LogEx( __WHERE_SHORT__,__VA_ARGS__)   		

#define STADD_WARNING(...) gpSimpleLogInstance->SetNowLogLevel(TLOG_WARNING), gpSimpleLogInstance->LogEx( __WHERE_SHORT__,__VA_ARGS__)

#define STADD_NORMAL(...) if(0 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(0),gpSimpleLogInstance->LogEx( __WHERE_SHORT__,__VA_ARGS__)  

#define STADD_FLOW(...)  if(1 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(1),gpSimpleLogInstance->LogEx( __WHERE_SHORT__,__VA_ARGS__) 
	
#define STADD_FUNC(...) if(2 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(2),gpSimpleLogInstance->LogEx( __WHERE_SHORT__,__VA_ARGS__)

#define STADD_DETAIL(...) if(3 <= gpSimpleLogInstance->m_iLogLevel)  \
		gpSimpleLogInstance->SetNowLogLevel(3),gpSimpleLogInstance->LogEx( __WHERE_SHORT__,__VA_ARGS__)

#define STADD_NORMAL_NO_SCREEN(...) if(0 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(0),gpSimpleLogInstance->LogEx( __WHERE_SHORT__,__VA_ARGS__)
#else
//sun�����±������

#define STADD_ERROR(FMT,...) gpSimpleLogInstance->SetNowLogLevel(TLOG_FATAL), gpSimpleLogInstance->Log(__WHEREFORMAT_SHORT__ FMT,__WHERE_SHORT__,##__VA_ARGS__)   		

#define STADD_WARNING(FMT,...) gpSimpleLogInstance->SetNowLogLevel(TLOG_WARNING), gpSimpleLogInstance->Log(__WHEREFORMAT_SHORT__ FMT,__WHERE_SHORT__,##__VA_ARGS__)

#define STADD_NORMAL(FMT,...) if(0 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(0),gpSimpleLogInstance->Log(__WHEREFORMAT_SHORT__ FMT,__WHERE_SHORT__,##__VA_ARGS__)   

#define STADD_FLOW(FMT,...)  if(1 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(1),gpSimpleLogInstance->Log(__WHEREFORMAT_SHORT__ FMT,__WHERE_SHORT__,##__VA_ARGS__)   
	
#define STADD_FUNC(FMT,...) if(2 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(2),gpSimpleLogInstance->Log(__WHEREFORMAT_SHORT__ FMT,__WHERE_SHORT__,##__VA_ARGS__)

#define STADD_DETAIL(FMT,...) if(3 <= gpSimpleLogInstance->m_iLogLevel)  \
		gpSimpleLogInstance->SetNowLogLevel(3),gpSimpleLogInstance->Log(__WHEREFORMAT_SHORT__ FMT,__WHERE_SHORT__,##__VA_ARGS__)

#define STADD_NORMAL_NO_SCREEN(FMT,...) if(0 <= gpSimpleLogInstance->m_iLogLevel) \
		gpSimpleLogInstance->SetNowLogLevel(0),gpSimpleLogInstance->Log(__WHEREFORMAT_SHORT__ FMT,__WHERE_SHORT__,##__VA_ARGS__)

#endif

#define SIS_LOG(x) if(x <= gpSimpleLogInstance->m_iLogLevel)
#define CHECK_RET(_ret,...) if((iRet = _ret)!= 0){ STADD_ERROR(__VA_ARGS__);return iRet;}
#define CHECK_OBJ(_obj) if(NULL == _obj){STADD_ERROR( #_obj" is null"); return -1;}
#define SAFE_DELETE(_obj) if(NULL != _obj){delete _obj;_obj=NULL;}
#define SAFE_DELETE_ARRAY(_obj) if(NULL != _obj){delete[] _obj;_obj=NULL;}


#endif 
