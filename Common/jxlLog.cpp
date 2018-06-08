////////////////////////////////////////////////
// Name: TLog.cpp
// Description: �̰߳�ȫ����־��
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
		//������ʼ��
	    m_bShowConsole = false;
	    m_iLogLevel = 0;  //��ǰ��־�ļ���
	    m_iLogSize  = 64; //�趨LOG�ļ����Ĵ�С����λΪM����������˴�С���򱸷��ļ�
	    m_iNowLogLevel = 0;
	    m_iPid = 0;
	    m_logFlag = true;
	    //��ȡ��־Ŀ¼
	    memset(m_sPath, 0, sizeof(m_sPath));
	    memset(m_pszFileName, 0, sizeof(m_pszFileName));
		memset(m_pszErrorFileName, 0, sizeof(m_pszErrorFileName));
	    //���AUTOTEST_HOME���������ڣ�����HOME��������
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
	
	//��ȡ���̺�
	int TLog::GetPID()
	{
	#ifdef WIN32
		return GetCurrentProcessId();
	#else
		return getpid();
	#endif
	}
	
	//��ȡ�̺߳�
	unsigned long TLog::GetTID()
	{
	#ifdef WIN32
		return GetCurrentThreadId();
	#else
		return pthread_self();
	#endif
	}
	//�Ƴ�file
	bool TLog::Remove(const char * sFileName)
	{
	    if (::remove(sFileName) != 0) 
	        return false;
	    else 
	        return true;
	}
	//������file
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
			//��ϵͳ������������
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
	    //��ȡ����LogLevel
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
	    //��������
	    m_iLogLevel    = iLevel;
	    m_bShowConsole = bFlag;
	}
	
	void TLog::End()
	{
	}
	
	void TLog::SetLogLevel(int iLevel)
	{
	    //���ý�����־����
	    //���ﻹ�����ô������־���
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
	
	//��¼������Ϣ��log,sFileName=��־���ļ�����sFileLine=����log��λ��
	void TLog::LogEx(const char * sFileName,int  iFileLine,const char * sFuncName,const char * fmt, ...)
	{
	    char sLogTemp[10240];
	    va_list ap;
	    va_start(ap,fmt);
	    vsnprintf(sLogTemp, sizeof(sLogTemp), fmt, ap); 
	    va_end (ap);
		Log("[%s:%d][%s]: %s",sFileName,iFileLine,sFuncName,sLogTemp);//��¼
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
		{//���ڴ�����־��ר��д��һ���ļ���ȥ
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
	
	
	//����ļ��Ƿ񳬳����ƣ����ǣ����䱸��Ϊ.old�ļ���������һ���µ��ļ�
	//����1Ϊ��־�ļ���������2Ϊ��־�ļ���Ӧ�ľ��
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
	    //�ж��ļ��Ƿ����
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
	
	        //����־�ļ�������
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
	    time(&tCurrent); //ȡ�õ�ǰʱ���time_tֵ
	    tm_Cur = localtime(&tCurrent); //ȡ�õ�ǰʱ���tmֵ
	    
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

