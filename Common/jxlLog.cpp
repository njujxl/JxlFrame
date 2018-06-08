////////////////////////////////////////////////
// Name: TLog.cpp
// Description: 线程安全的日志类
////////////////////////////////////////////////
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <sstream>
#include <errno.h>
#include <sys/stat.h>
#include <pthread.h>
//#include "App/TStringFunc.h"


#include "jxlLog.h"
#ifdef  _WIN32
    #include <time.h>
    #include <windows.h>
#else
    #include <unistd.h>
#endif  //_UNIX

#ifndef WIN32
  #include <unistd.h>
#else
  #include <process.h>
  
  #include <io.h>
  #include <direct.h>
#endif

using namespace std;
namespace JxlFrame{
	TLog* gpSimpleLogInstance = new(std::nothrow) TLog();
	
	TLog::TLog()
	{
		//变量初始化
	    m_bShowConsole = false;
	    m_iLogLevel = 0;  //当前日志的级别
	    m_iLogSize  = 64; //设定LOG文件最大的大小，单位为M，如果超出此大小，则备份文件
	    m_iNowLogLevel = 0;
	    m_iPid = 0;
	    m_logFlag = true;
	    //获取日志目录
	    memset(m_sPath, 0, sizeof(m_sPath));
	    memset(m_pszFileName, 0, sizeof(m_pszFileName));
		memset(m_pszErrorFileName, 0, sizeof(m_pszErrorFileName));
	    //如果AUTOTEST_HOME变量不存在，则找HOME环境变量
	    if(NULL == getenv("FSTEST_HOME"))
	    {
	        snprintf(m_sPath,sizeof(m_sPath),"%s",getenv("HOME"));
	    }
	    else
	    {
	        snprintf(m_sPath,sizeof(m_sPath),"%s",getenv("FSTEST_HOME"));
	    }
		#ifdef WIN32
	    	snprintf(m_sPath+strlen(m_sPath),sizeof(m_sPath)-strlen(m_sPath), "\\%s\\","log");
		#else
	        snprintf(m_sPath+strlen(m_sPath),sizeof(m_sPath)-strlen(m_sPath), "/%s/","log");
		#endif
	    if(!IsExist(m_sPath))
	    {
	    	Mkdir(m_sPath);
	    }
	}
	
	
	TLog::~TLog()
	{
		
	}
	
	bool TLog::Mkdir(const char * sPath)
	{
	    int rtn = -1;
	#if defined(__OS_WINDOWS__)
	    rtn = ::mkdir(sPath);
	#elif defined(__OS_UNIX__)
	    rtn = 0;//::mkdir(sPath, O_CREAT|S_IRUSR|S_IWUSR|S_IXUSR);
	    for(int i=0; i<strlen(sPath); ++i)
	    {
	        if(sPath[i] == '/')
	        {
	            char sDir[256];
	            memset(sDir, 0, sizeof(sDir));
	            strncpy(sDir, sPath, i);
	            
	            if(IsExist(sDir) == false)
	            {
	                rtn = ::mkdir(sDir, O_CREAT|S_IRUSR|S_IWUSR|S_IXUSR);                    
	            }
	        }    
	    }
	#endif 
	    return rtn == 0;
	}
	
	bool TLog::IsExist(const char *sFileName)
	{
	    int iRetCode =0;
	#ifndef _WIN32
	    iRetCode = access(sFileName, F_OK);
	#else
	    iRetCode = access(sFileName, 0x00);
	#endif
	    return iRetCode == 0;
	}
	
	//获取进程号
	int TLog::GetPID()
	{
	#ifdef WIN32
		return GetCurrentProcessId();
	#else
		return getpid();
	#endif
	}
	
	//获取线程号
	unsigned long TLog::GetTID()
	{
	#ifdef WIN32
		return GetCurrentThreadId();
	#else
		return pthread_self();
	#endif
	}
	//移除file
	bool TLog::Remove(const char * sFileName)
	{
	    if (::remove(sFileName) != 0) 
	        return false;
	    else 
	        return true;
	}
	//重命名file
	bool TLog::Rename(const char * srcFileName, const char * desFileName, bool bSameFileSystem)
	{
		if (!IsExist(srcFileName))
		{
			cout << "SrcFile [" << srcFileName << "]" << "Not Exist." << endl; 
			return false;
		}
		#if defined(__OS_WINDOWS__)
		::rename(srcFileName, desFileName);
		#else
		if (bSameFileSystem)
		{
			int iRet = rename(srcFileName, desFileName);
			if (iRet==0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			//用系统命令处理改名操作
			char sCmdLine[1024];
			sprintf(sCmdLine,"mv %s %s",srcFileName, desFileName);
			system(sCmdLine);
		}
		#endif
		if (IsExist(srcFileName)==false) 
			return true;
		else
			return false;
	}
	
	
	
	void TLog::Start(const char *sAppName, int iLevel, bool bFlag)
	{
	    if(iLevel == -1)
	    {
	        m_logFlag = false;
	        return;
	    }
	    int i = 0;
	    //获取配置LogLevel
	    memset(m_sAppName,'\0',sizeof(m_sAppName));
	    //S_SAFESTRCPY(m_sAppName,sizeof(m_sAppName), sAppName);
	    strncpy(m_sAppName, sAppName, sizeof(m_sAppName));
	    m_sAppName[strlen(m_sAppName)] = '\0';	
	#ifndef _WIN32
	    if (strlen(m_pszFileName) == 0)
	    {
			sprintf(m_pszFileName,"%s/%s.log", m_sPath, sAppName);
			sprintf(m_pszErrorFileName,"%s/%s.log_ERROR", m_sPath, sAppName);
	   	}
	#else
		sprintf(m_pszFileName,"%s\\%s.log", m_sPath, sAppName);
		sprintf(m_pszErrorFileName,"%s\\%s.log_ERROR", m_sPath, sAppName);
	#endif
	    //其他配置
	    m_iLogLevel    = iLevel;
	    m_bShowConsole = bFlag;
	}
	
	void TLog::End()
	{
	}
	
	void TLog::SetLogLevel(int iLevel)
	{
	    //设置进程日志级别
	    //这里还是设置传入的日志界别
	    if(m_logFlag == false)
	    {
	        return;
	    }
	    m_iLogLevel = iLevel;
	}
	
	int TLog::GetNowLogLevel()
	{
	    if(m_logFlag == false)
	    {
	        return 0;
	    }
		return m_iNowLogLevel;
	}
	
	
	void TLog::SetLogSize(int iLogSize)
	{
	    if(m_logFlag == false)
	    {
	        return;
	    }
	    m_iLogSize = iLogSize ;
	}
	
	int TLog::GetLogSize()
	{
	    if(m_logFlag == false)
	    {
	        return 0;
	    }
	    return m_iLogSize ;
	}
	
	
	void TLog::SetShowConsole(bool bFlag)
	{
	    if(m_logFlag == false)
	    {
	        return;
	    }
	    m_bShowConsole = bFlag;
	}
	void TLog::GetLevelName(int iLogLevel, char sInfo[])
	{
	    if(m_logFlag == false)
	    {
	        return;
	    }
	    switch(iLogLevel)
	    {
	    case TLOG_FLOW       : strcpy(sInfo,"[ FLOW ]");break;
	    case TLOG_DETAIL     : strcpy(sInfo,"[DETAIL]");break;
	    case TLOG_FUNC       : strcpy(sInfo,"[ FUNC ]");break;
	    case TLOG_WARNING    : strcpy(sInfo,"[ WARN ]");break;
	    case TLOG_FATAL      : strcpy(sInfo,"[ ERROR]");break;
	    case TLOG_NORMAL     : strcpy(sInfo,"[NORMAL]");break;
	    default              : strcpy(sInfo,"[ (N/A)]");break;
	    }
	}
	
	//记录额外信息的log,sFileName=日志的文件名，sFileLine=调用log的位置
	void TLog::LogEx(const char * sFileName,int  iFileLine,const char * sFuncName,const char * fmt, ...)
	{
	    char sLogTemp[10240];
	    va_list ap;
	    va_start(ap,fmt);
	    vsnprintf(sLogTemp, sizeof(sLogTemp), fmt, ap); 
	    va_end (ap);
		Log("[%s:%d][%s]: %s",sFileName,iFileLine,sFuncName,sLogTemp);//记录
	}
	
	void TLog::Log(const char * fmt, ...)
	{
	    if(m_logFlag == false)
	    {
	        return;
	    }
	    char sDate[30], sInfo[15];
	    FILE * fp = NULL;
	    GetCurrentTimeStr(sDate, sizeof(sDate), true);
	   	
	    GetLevelName(m_iNowLogLevel, sInfo);
	    char sLogTemp[10240];
	    va_list ap;
	    va_start(ap,fmt);
	    vsnprintf(sLogTemp, sizeof(sLogTemp), fmt, ap); 
	    va_end (ap);
	    if (m_iNowLogLevel <= 0)
	    {
	        if(m_bShowConsole == true)
	        {
	        	printf("[%d-%lu] %s|%s\n", GetPID(),GetTID(), sInfo, sLogTemp); 
	        }
	        else
	        {
	        	if(m_iNowLogLevel < 0)
	        	{
	        		printf("[%d-%lu] %s|%s\n", GetPID(),GetTID(), sInfo, sLogTemp); 
	        	}
	        }
	    }
	#ifdef WIN32 
		if(fp!=NULL)
			fclose(fp);
	#endif
	    fp = fopen(m_pszFileName, "a+");
	    if(fp == NULL) 
	    {
	        printf("TLog::Log(%s) : Open file [%s] failed. \n", m_sAppName,m_pszFileName);
	        return ;
		}
	    else
	    {
	        CheckAndBackup(m_pszFileName, fp);
	        fprintf(fp, "%s %s [%d-%lu]|%s\n", sDate, sInfo, GetPID(),GetTID(), sLogTemp);
	        fflush(fp);
	    }
	    fclose(fp);
	
		if(TLOG_FATAL == m_iNowLogLevel)
		{//对于错误日志的专门写到一个文件中去
			FILE * fpErr = NULL;
			#ifdef WIN32 
			if(fpErr!=NULL)
				fclose(fpErr);
			#endif
		    fpErr = fopen(m_pszErrorFileName, "a+");
		    if(fpErr == NULL) 
		    {
		      printf("TLog::Log(%s) : Open file [%s] failed. \n", m_sAppName,m_pszErrorFileName);
	
	          return;
		    }
		    else
		    {
		        CheckAndBackup(m_pszErrorFileName, fpErr);
		        fprintf(fpErr, "%s %s [%d-%lu]|%s\n", sDate, sInfo, GetPID(),GetTID(), sLogTemp);
		        fflush(fpErr);
		    }
		    fclose(fpErr);
		}
	    
	}
	
	
	long TLog::GetFileSize(char * sFullPathFileName)
	{
	    if(m_logFlag == false)
	    {
	        return 0;
	    }
	    struct stat sbuf;
	    if (stat(sFullPathFileName, &sbuf) == 0)
	        return sbuf.st_size;
	    else 
	        return -1;
	}
	
	
	//检查文件是否超出限制，若是，则将其备份为.old文件，并创建一个新的文件
	//参数1为日志文件名，参数2为日志文件对应的句柄
	bool TLog::CheckAndBackup(const char * sFileName , FILE*& fp)
	{
	    if(m_logFlag == false)
	    {
	        return true;
	    }
		//return true;
		
	    char     sFileNameOld[255];
	    long     filesize = -1 ;
	    int      filehandle = -1 ;
	    struct stat buf;
	    memset(sFileNameOld,0, 255);
	    //判断文件是否存在
	    if(stat(sFileName,&buf)<0)
	    {
	   		if(errno == ENOENT)
	   		{
	   		        fclose(fp);
	   		        fp = fopen(sFileName,"a+");
	   		}
	    }
	    filesize = GetFileSize((char*)sFileName);
	
	    if (filesize == -1) 
	    {
	    	return false;
	    }
	    
	    if (filesize >= m_iLogSize*1024*1024)	
	    {
	       	fclose(fp);
	        Remove(sFileNameOld);
	        sprintf(sFileNameOld,"%s.%s", sFileName, "old");
	
	        //将日志文件重命名
	        Rename(sFileName,sFileNameOld,true);
			
	        Remove(sFileName);
	
	#ifndef _WIN32
	        filehandle = open(sFileName,O_CREAT|O_EXCL,0666);
	        if ( filehandle != -1 ) 
	        {
	            close( filehandle );
	            chmod(sFileName, 0666);
	        }
	#endif
	        fp = fopen (sFileName,"a+");
	        if(fp == NULL)
	        {
	            printf("Check And Backup Log File: Open file [%s] fail.\n",sFileName);
	            return false;
	        }
	    }
	    return true ;
	}
	
	
	void TLog::GetCurrentTimeStr(char sTime[], size_t iLen, const bool bLongFlag)
	{
	    time_t tCurrent;
	    struct tm *tm_Cur;
	    char sCurtime[40];
	    sCurtime[39]=0;
	    time(&tCurrent); //取得当前时间的time_t值
	    tm_Cur = localtime(&tCurrent); //取得当前时间的tm值
	    
	    if(bLongFlag)
	    {
	        sprintf(sCurtime,"%04d-%02d-%02d %02d:%02d:%02d",tm_Cur->tm_year+1900,tm_Cur->tm_mon+1,tm_Cur->tm_mday,tm_Cur->tm_hour,tm_Cur->tm_min,tm_Cur->tm_sec);
	    }
	    else
	    {
	        sprintf(sCurtime,"%04d%02d%02d%02d%02d%02d",tm_Cur->tm_year+1900,tm_Cur->tm_mon+1,tm_Cur->tm_mday,tm_Cur->tm_hour,tm_Cur->tm_min,tm_Cur->tm_sec);
	    }
	
	    if(sTime!=NULL)
	    {
	        if(iLen>0)
	        {
	            strncpy(sTime,sCurtime,iLen-1);
	            sTime[iLen-1]='\0';
	        }
	        else
	            strcpy(sTime,sCurtime);
	    }
	
	    return;
	}
}

