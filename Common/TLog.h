//注意:在统一个线程中,不允许多次使用TADD_START,否则会覆盖.

#ifndef __AUTOTEST_LOG_H__
#define __AUTOTEST_LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
using namespace std;

#define  TLOG_NORMAL       0     //正常日志, 无论如何都记录(处理文件(批量)级)
#define  TLOG_FLOW         1     //详细日志(记录级)
#define  TLOG_FUNC         2     //一般调试日志, 输出函数调用过程
#define  TLOG_DETAIL       3     //详细调试记录, 输出运行时数据

#define  TLOG_WARNING -100     //一般告警(数据错误)
#define  TLOG_FATAL   -200     //严重告警(系统资源不足, 程序断言失败)

#define MAX_THREAD_COUNTS 128
#define MAX_SYSTEM_THREAD_COUNTS 32
#define MAX_BUSINESS_NAME_LEN 32
#define MAX_PATH_NAME_LEN 256
#define MAX_LOG_BUFFER_LEN 10240

//系统日志类
class TLog 
{
public:
    void Release();
public:
    void Start(const char * sAppName, int iLevel, bool bFlag);
    void End();
    void Log(const char * fmt, ...);
	void LogEx(const char * sFileName,int  iFileLine,const char * sFuncName,const char * fmt, ...);//记录额外信息的log
	
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
    int  m_iLogLevel;     //设定的日志的级别
    char m_sPath[MAX_PATH_NAME_LEN];	
    char m_pszFileName[MAX_PATH_NAME_LEN];
	char m_pszErrorFileName[MAX_PATH_NAME_LEN];//只记录错误日志
    int m_iNowLogLevel;
private:
	int GetPID();//获取进程号
	unsigned long GetTID();//获取线程号
	bool Remove(const char * sFileName);
	bool Rename(const char * srcFileName, const char * desFileName, bool bSameFileSystem);
	bool Mkdir(const char * sPath);
private:
    bool m_bShowConsole;  //是否在屏幕打印  
    int  m_iLogSize;      //设定LOG文件最大的大小，单位为M，如果超出此大小，则备份文件
    int iPos ;
    char m_sAppName[32];
    int m_iPid;
	bool m_logFlag;//日志是否生效
};

extern "C" TLog* gpSimpleLogInstance;      //单个实例

//是否使用日志,TADD == Thread Add
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

//定义打印信息宏
#define __WHERE_SHORT__ __FILE__,__LINE__,__FUNCTION__
#define __WHEREFORMAT_SHORT__ "[%s:%d][%s]: "

//add by jin.shaohua
#ifdef OS_SUN
#define __FUNCTION__ ""
//sun环境中不支持##消除逗号所以在外面包了一层
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
//sun机器下编译错误

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
