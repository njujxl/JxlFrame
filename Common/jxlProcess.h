#ifndef __JXLPROCESS_H__
#define __JXLPROCESS_H__

#include "jxlOS.h"

//using namespace JxlFrame;
using namespace std;
namespace JxlFrame
{
	class CJxlProcess
	{
	public:
		CJxlProcess();
		CJxlProcess(char * processName);
		~CJxlProcess();
		int Start();
		int Stop();
	private:
		char m_cProcessName[MAX_PROCESS_NAME_LENGTH];
	};
}
#endif //__JXLPROCESS_H__
