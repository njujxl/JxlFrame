#ifndef _JXLJOB_H__
#define _JXLJOB_H__

#include "jxlThread.h"
#include "jxlRand.h"
#include "Interface/mdbQuery.h"
#include "Helper/TOraDBQuery.h"
#include "Helper/dgDBInterface.h"
#ifdef DB_ORACLE
#include "Helper/TOraDBQuery.h"
#elif DB_MYSQL
#include "Helper/TMsqDBQuery.h"
#endif
#include <unistd.h>

//using namespace QuickMDB;
namespace JxlFrame
{
	class CJxlJob : public CJxlThread
	{
	public:
		CJxlJob();
		~CJxlJob();
		void run();
	};
}


#endif //_JXLJOB_H__