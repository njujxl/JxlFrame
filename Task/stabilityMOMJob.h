#ifndef _STABILITYMOMJOB_H__
#define _STABILITYMOMJOB_H__

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

namespace JxlFrame
{
	class CStabilityMOMJob : public CJxlThread
	{
	public:
		CStabilityMOMJob();
		~CStabilityMOMJob();
		void run();
	};
}


#endif //_STABILITYMOMJOB_H__