#include "deleteJob.h"

using namespace JxlFrame;

using namespace std;

int main(int argc, char* argv[])
{
	int iRet = 0;
	CDeleteJob* job = new CDeleteJob();
	job->start();
	job->join();
	return iRet;
}