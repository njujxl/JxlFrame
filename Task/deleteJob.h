#ifndef _DELETEJOB_H__
#define _DELETEJOB_H__

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
	class CDeleteJob : public CJxlThread
	{
	public:
		CDeleteJob();
		~CDeleteJob();
		void run();
	};
}


#endif //_DELETEJOB_H__