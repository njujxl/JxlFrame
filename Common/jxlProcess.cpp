#include "jxlProcess.h"
namespace JxlFrame
{
	CJxlProcess::CJxlProcess()
	{
		
	}
	
	CJxlProcess::CJxlProcess(char * processName)
	{
		memset(m_cProcessName, 0, sizeof(m_cProcessName));
		strcpy(m_cProcessName, processName);
	}
	
	CJxlProcess::~CJxlProcess()
	{
	
	}
	
	int CJxlProcess::Start()
	{
		int iRet = 0;
		system(m_cProcessName);
		return iRet;
	}
	
	int CJxlProcess::Stop()
	{
		int iRet = 0;
		int iPid[MAX_PROC_COUNT] = {0};
		CJxlOS::GetPidByName(m_cProcessName, iPid);
		for(int i = 0; i < MAX_PROC_COUNT; i++)
		{
			if(iPid[i] > 0)
			{
				CJxlOS::KillProc(iPid[i]);
			}
		}
		return iRet;
	}
	
}
