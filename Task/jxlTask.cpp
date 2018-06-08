#include "jxlJob.h"
#include <unistd.h>

using namespace JxlFrame;

using namespace std;

int main(int argc, char* argv[])
{
	int iRet;
	CJxlJob* job0 = new CJxlJob();
	//CJxlJob* job1 = new CJxlJob();
	job0->start();
	//job1->start();
	job0->join();
	//job1->join();
	
	return iRet;
}