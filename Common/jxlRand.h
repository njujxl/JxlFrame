#ifndef __JXLRAND_H__
#define __JXLRAND_H__

#include "stdlib.h"

//using namespace JxlFrame;
using namespace std;
namespace JxlFrame
{
	class CJxlRand
	{
	public:
		CJxlRand();
		~CJxlRand();
		static int GetRandNum();
		static int GetRandNum(int iEnd);
		static int GetRandNum(int iStart, int iEnd);
		static char GetRandChar();
		static int GetRandStr(char * pStr, int iLen);
		//static const char * GetRandDateStr();
	};
}
#endif //__JXLRAND_H__
