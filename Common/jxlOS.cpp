#include "jxlOS.h"
using namespace std;
namespace JxlFrame
{
	CJxlOS::CJxlOS()
	{
		
	}
	
	CJxlOS::~CJxlOS()
	{
		
	}
	
	int CJxlOS::GetPid()
	{
		return getpid();
	}
	
	int CJxlOS::GetPidByName(const char* processName, int pid[])
	{
		char buf[10];
	    char Cmd[100];
	    int i = 0;
	    FILE *p;
	    memset(Cmd,0,sizeof(Cmd));
	    sprintf(Cmd,"%s\"%s\"%s","ps -fu $LOGNAME |grep -v grep|grep ",processName,"|awk '{print $2}'");
	    cout << Cmd << endl;
	    Cmd[strlen(Cmd)] = '\0';
	    p = popen(Cmd,"r");
	    if(p == NULL)
	    {
	        cout << "ERROR" << endl;
	        return 0;
	    }
	    while(1)
	    {
	        memset(buf,0,sizeof(buf));
	        fgets(buf,sizeof(buf),p);
	        if(strlen(buf)==0)
	        {
	            break;
	        }
	        pid[i] = atoi(buf);
	        i++;
	    }
	    pclose(p);
	    return 0;
	}
	
	int CJxlOS::GetPidByFullName()
	{
		
	}
	
	int CJxlOS::GetProcNameByPid()
	{
		
	}
	
	int CJxlOS::GetProcFullNameByPid()
	{
		
	}
	
	bool CJxlOS::IsProcExist(int pid)
	{
		
	}
	
	bool CJxlOS::IsProcExistByKill()
	{
		
	}
	
	bool CJxlOS::IsProcExistByOpen()
	{
		
	}
	
	int CJxlOS::KillProc(int pid)
	{
		
	}
	
	int CJxlOS::GetTid()
	{
		return pthread_self();
	}
}

