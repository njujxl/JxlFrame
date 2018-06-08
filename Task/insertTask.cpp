#include "insertJob.h"

using namespace JxlFrame;

using namespace std;

int main(int argc, char* argv[])
{
	int iRet = 0;
	
	/*
	char * m_sUser = "jxl";
	char * m_sPassword = "jxl";
	char * m_sDsn = "jxl";
	TMdbDatabase* m_pDataBase = new(std::nothrow) TMdbDatabase();
	m_pDataBase->SetLogin(m_sUser,m_sPassword,m_sDsn);
	if(m_pDataBase->Connect() == false)
	{
		cout << "Connect failed!" << endl;
	}
		
	TMdbQuery* m_pQuery = m_pDataBase->CreateDBQuery();
	m_pQuery->CloseSQL();
	m_pQuery->SetSQL("insert into PCC_SESSION (SESSION_ID, USER_NAME, FRAMED_IP_ADDRESS) values (:SESSION_ID, :USER_NAME, :FRAMED_IP_ADDRESS);");
	
	int i = 0;
	char * sBase = "pdsnjkt2-2.smart.com;1469709847;148697554;";
	char sSessionID[64] = {0};
	char sUserName[32] = {0};
	char sIP[32] = {0};
	
	for(i = 0; i<2000000; i++)
	{
		if(i%10000 == 0) 
		{
			m_pQuery->Commit();
		}
		CJxlRand::GetRandStr(sUserName, 30);
		CJxlRand::GetRandStr(sIP, 30);
		snprintf(sSessionID, sizeof(sSessionID), "%s%d", sBase, i);
		m_pQuery->SetParameter("SESSION_ID", sSessionID);
		m_pQuery->SetParameter("USER_NAME", sUserName);
		m_pQuery->SetParameter("FRAMED_IP_ADDRESS", sIP);
		m_pQuery->Execute();
		//usleep(30);
	}
	m_pQuery->Commit();
	printf("OK!\n");
	sleep(60);
	printf("Prepare OK!\n");
	*/
	CInsertJob* job = new CInsertJob();
	job->start();
	job->join();
	return iRet;
}