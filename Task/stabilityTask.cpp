#include "stabilityMOMJob.h"

using namespace JxlFrame;

using namespace std;

int main(int argc, char* argv[])
{
	int iRet;
	/*
	char pk1_base[] = "adsfadlkl;kghplakd;ljgoi;werpsa[kgk;kjsa;kldkfjlkwerjhg;lka;ldgj;okerjgh;klajsd;klfj;oiwerhg;lkajef;hwero;gj;akjreg;kojre;odksd";
	char sPk1[128] = {0};
	
	char * m_sUser = "jxl";
	char * m_sPassword = "jxl";
	char * m_sDsn = "jxl";
	
	try
	{
		TMdbDatabase* m_pDataBase = new(std::nothrow) TMdbDatabase();
		m_pDataBase->SetLogin(m_sUser,m_sPassword,m_sDsn);
		if(m_pDataBase->Connect() == false)
		{
			cout << "Connect failed!" << endl;
		}
		TMdbQuery* m_pQuery = m_pDataBase->CreateDBQuery();
		m_pQuery->CloseSQL();
		
		m_pQuery->SetSQL("delete from RESERVE_BAL where 1;");
		m_pQuery->Execute();
		m_pQuery->Commit();
		m_pQuery->Close();
		m_pQuery->SetSQL("insert into RESERVE_BAL (SESSION_ID, BAL_ID, ACCT_ID, BAL_SHARE_ID, USED_BAL, RESERVE_BAL, UPDATE_DATE) values (:SESSION_ID, :BAL_ID, :ACCT_ID, :BAL_SHARE_ID, :USED_BAL, :RESERVE_BAL, sysdate);");
		
		int i = 0;
		time_t timer = time(NULL);
		printf("ctime: %s\n", ctime(&timer));
		for(i = 0; i<5000000; i++)
		{
			if(i!=0 && i%10000 == 0) m_pQuery->Commit();
			//memset(sPk1, 0, sizeof(sPk1));
			snprintf(sPk1, CJxlRand::GetRandNum(75, 115), "%s", pk1_base);
			snprintf(sPk1+strlen(sPk1), sizeof(sPk1) - strlen(sPk1), "%d", i);
			m_pQuery->SetParameter(0, sPk1);
			m_pQuery->SetParameter(1, i);
			m_pQuery->SetParameter(2, i);
			m_pQuery->SetParameter(3, i);
			m_pQuery->SetParameter(4, i);
			m_pQuery->SetParameter(5, i);
			m_pQuery->Execute();
		}
		m_pQuery->Commit();
		timer = time(NULL);
		printf("ctime: %s\n", ctime(&timer));
	}
	catch(TMdbException &e)
	{
		return iRet;
	}
	
	CStabilityMOMJob* job0 = new CStabilityMOMJob();
	CStabilityMOMJob* job1 = new CStabilityMOMJob();
	CStabilityMOMJob* job2 = new CStabilityMOMJob();
	CStabilityMOMJob* job3 = new CStabilityMOMJob();
	CStabilityMOMJob* job4 = new CStabilityMOMJob();
	CStabilityMOMJob* job5 = new CStabilityMOMJob();
	CStabilityMOMJob* job6 = new CStabilityMOMJob();
	CStabilityMOMJob* job7 = new CStabilityMOMJob();
	CStabilityMOMJob* job8 = new CStabilityMOMJob();
	CStabilityMOMJob* job9 = new CStabilityMOMJob();
	job0->start();
	job1->start();
	job2->start();
	job3->start();
	job4->start();
	job5->start();
	job6->start();
	job7->start();
	job8->start();
	job9->start();
	job0->join();
	job1->join();
	job2->join();
	job3->join();
	job4->join();
	job5->join();
	job6->join();
	job7->join();
	job8->join();
	job9->join();
	*/
	
	CStabilityMOMJob* job0 = new CStabilityMOMJob();
	job0->start();
	job0->join();
	
	return iRet;
}