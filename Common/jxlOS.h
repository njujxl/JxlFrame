#ifndef __JXLOS_H__
#define __JXLOS_H__

#include "jxlStruct.h"
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
/*
#include <errno.h>
#include <sys/statvfs.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <net/if_arp.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<stdlib.h>
*/

//using namespace JxlFrame;
namespace JxlFrame
{
	class CJxlOS
	{
	public:
		CJxlOS();
		~CJxlOS();
		//进程相关方法
		static int GetPid();
		static int GetPidByName(const char* processName, int pid[]);
		static int GetPidByFullName();
		static int GetProcNameByPid();
		static int GetProcFullNameByPid();
		static bool IsProcExist(int pid);
		static bool IsProcExistByKill();
		static bool IsProcExistByOpen();
		static int KillProc(int pid);
		//线程相关方法
		static int GetTid();
	};
}
#endif //__JXLOS_H__