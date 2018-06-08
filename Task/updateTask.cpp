#include "updateJob.h"

using namespace JxlFrame;

using namespace std;

int main(int argc, char* argv[])
{
	int iRet = 0;
	CUpdateJob* job = new CUpdateJob();
	job->start();
	job->join();
	return iRet;
}