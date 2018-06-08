#ifndef _STABILITYOMJOB_H__
#define _STABILITYOMJOB_H__

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
	class CStabilityOMJob : public CJxlThread
	{
	public:
		CStabilityOMJob();
		~CStabilityOMJob();
		void run();
	};
}


#endif //_STABILITYOMJOB_H__