#ifndef _INSERTJOB_H__
#define _INSERTJOB_H__

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
	class CInsertJob : public CJxlThread
	{
	public:
		CInsertJob();
		~CInsertJob();
		void run();
	};
}


#endif //_INSERTJOB_H__