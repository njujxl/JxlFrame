#include "Common/jxlOS.h"
#include "Common/jxlProcess.h"
#include <stdlib.h>
#include <iostream>
using namespace JxlFrame;
using namespace std;

int main(int argc, char* argv[])
{
	int iRet = 0;
	if(argc > 1)
	{
		CJxlProcess * proc = NULL;
		char sProcName[MAX_PROCESS_NAME_LENGTH] = {0};
		strncpy(sProcName, argv[1], strlen(argv[1]));
		strncpy(sProcName + strlen(sProcName), "Task", strlen("Task"));
		proc = new CJxlProcess(sProcName);
		int iPid[450] = {0};
//		CJxlOS::GetPidByName(sProcName, iPid);
//		if(iPid[0] > 0)
//		{
//			cout << "Process " << sProcName << " is already exist." << endl;
//			return iRet;
//		}
		proc->Start();
	}
	else
	{
		iRet = -1;
		cout << "Invalid argc." << endl;
	}
	return iRet;
}