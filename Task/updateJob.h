#ifndef _UPDATEJOB_H__
#define _UPDATEJOB_H__

#include "jxlThread.h"
#include "jxlRand.h"
#ifdef DB_ORACLE
#include "Helper/TOraDBQuery.h"
#elif DB_MYSQL
#include "Helper/TMsqDBQuery.h"
#endif
#include "Interface/mdbQuery.h"
#include "Interface/mdbClientQuery.h"
#include <unistd.h>

//using namespace QuickMDB;
namespace JxlFrame
{
	class CUpdateJob : public CJxlThread
	{
	public:
		CUpdateJob();
		~CUpdateJob();
		void run();
	};
}


#endif //_UPDATEJOB_H__