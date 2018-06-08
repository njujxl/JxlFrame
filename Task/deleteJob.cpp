#include "deleteJob.h"
namespace JxlFrame
{
	CDeleteJob::CDeleteJob()
	{
		
	}
	
	CDeleteJob::~CDeleteJob()
	{
		
	}
	
	void CDeleteJob::run()
	{
		/*char * m_sUser = "jxl";
		char * m_sPassword = "jxl";
		char * m_sDsn = "jxl";
		TMdbDatabase* m_pDataBase = new(std::nothrow) TMdbDatabase();
		m_pDataBase->SetLogin(m_sUser,m_sPassword,m_sDsn);
		if(m_pDataBase->Connect() == false)
		{
			cout << "Connect failed!" << endl;
		}
		
		TMdbQuery* m_pSelQuery = m_pDataBase->CreateDBQuery();
		m_pSelQuery->CloseSQL();
		m_pSelQuery->SetSQL("select count(*) from numpk_mdb2mdb;");
		
		TMdbQuery* m_pMaxPkSelQuery = m_pDataBase->CreateDBQuery();
		m_pMaxPkSelQuery->CloseSQL();
		m_pMaxPkSelQuery->SetSQL("select MAX(pk1) from numpk_mdb2mdb;");
		
		TMdbQuery* m_pPkSelQuery = m_pDataBase->CreateDBQuery();
		m_pPkSelQuery->CloseSQL();
		m_pPkSelQuery->SetSQL("select pk1 from numpk_mdb2mdb where pk1<:pk1 limit 100;");
		
		TMdbQuery* m_pQuery = m_pDataBase->CreateDBQuery();
		m_pQuery->CloseSQL();
		m_pQuery->SetSQL("delete from numpk_mdb2mdb where pk1 = :pk1;");
		
		int iCount = 0;
		int iRound = 0;
		int iMaxPk = 0;
		int iPk = 0;
		time_t timer;
		
		while(true)
		{
			//timer = time(NULL);
			//printf("ctime: %s\n", ctime(&timer));
			
			if(iRound % 100000 == 0)
			{
				m_pSelQuery->Open();
				while(m_pSelQuery->Next())
				{
					iCount = m_pSelQuery->Field(0).AsInteger();
				}
				
				m_pMaxPkSelQuery->Open();
				while(m_pMaxPkSelQuery->Next())
				{
					iMaxPk = m_pMaxPkSelQuery->Field(0).AsInteger();
				}
				
			}
			if(iCount < 7000000)
			{
				iRound++;
				usleep(10000);
				continue;
			}
			//timer = time(NULL);
			//printf("Total [%d] records now, begin to delete, ctime: %s\n", iCount, ctime(&timer));
			
			m_pPkSelQuery->SetParameter(0, CJxlRand::GetRandNum(iMaxPk));
			m_pPkSelQuery->Open();
			while(m_pPkSelQuery->Next())
			{
				iPk = m_pPkSelQuery->Field(0).AsInteger();
				m_pQuery->SetParameter(0, iPk);
				m_pQuery->Execute();
			}
			m_pQuery->Commit();
			iRound++;
			usleep(100000);
		}*/
		
		
		try
		{
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
			m_pQuery->SetSQL("delete from PCC_SESSION where  SESSION_ID=:SESSION_ID;");
			
			int i = 0;
			
			char * sBase = "pdsnjkt2-2.smart.com;1469709847;148697554;";
			char sSessionID[64] = {0};
			char sUserName[32] = {0};
			char sIP[32] = {0};
			
			i = 0;
			while(true)
			{
				if(i == 3000000)
				{
					i = 0;
				}
				if(i%10000 == 0) 
				{
					m_pQuery->Commit();
				}
				snprintf(sSessionID, sizeof(sSessionID), "%s%d", sBase, i);
				m_pQuery->SetParameter("SESSION_ID", sSessionID);
				m_pQuery->Execute();
				i++;
				usleep(1000);
			}
		}
		catch(TMdbException &e)
		{
			
		}
	}
}

