#ifndef __JXLSTRUCT_H__
#define __JXLSTRUCT_H__

#include <stdlib.h>

//#define random(a,b) (rand()%(b-a) + a)

namespace JxlFrame
{
	#define MAX_PROC_COUNT 450  //最大进程数量
	#define MAX_PROCESS_NAME_LENGTH 256  //最大进程名长度
	
	//FS_TEST
	#define MAX_SQL_LENGTH 10000
	#define SQL_OPER_TYPE_SELECT 1
	#define SQL_OPER_TYPE_INSERT 2
	#define SQL_OPER_TYPE_UPDATE 3
	#define SQL_OPER_TYPE_DELETE 4
	#define SQL_OPER_TYPE_COMMIT 5
	#define SQL_OPER_TYPE_ROLLBACK 6
		
	#define MAX_PK_NUM 100000
	#define MAX_INT_NUM 99999999
	#define MAX_COL_NUM 5
}

#endif //__JXLSTRUCT_H__