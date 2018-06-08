#include "jxlRand.h"
namespace JxlFrame
{
	CJxlRand::CJxlRand()
	{
		
	}
	
	CJxlRand::~CJxlRand()
	{
	
	}
	
	int CJxlRand::GetRandNum()
	{
		return rand();
	}

	int CJxlRand::GetRandNum(int iEnd)
	{
		if(iEnd <= 0)
		{
			return -1;
		}
		else 
		{
			return rand()%iEnd;
		}
	}

	int CJxlRand::GetRandNum(int iStart, int iEnd)
	{
		if(iStart >= iEnd)
		{
			return -1;
		}
		else 
		{
			return rand()%(iEnd - iStart) + iStart;
		}
	}

	char CJxlRand::GetRandChar()
	{
		return static_cast<char>(GetRandNum(97, 123));
	}

	int CJxlRand::GetRandStr(char * pStr, int iLen)
	{
		if(pStr == NULL || iLen <= 0) return -1;
		for(int i = 0; i < iLen; i++)
		{
			pStr[i] = GetRandChar();
		}
		return 1;
	}
}