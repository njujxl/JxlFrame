#include "insertJob.h"
namespace JxlFrame
{
	CInsertJob::CInsertJob()
	{
		
	}
	
	CInsertJob::~CInsertJob()
	{
		
	}
	
	void CInsertJob::run()
	{
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
		
		TMdbQuery* m_pSelQuery = m_pDataBase->CreateDBQuery();
		m_pSelQuery->CloseSQL();
		m_pSelQuery->SetSQL("select count(*) from numpk_mdb2mdb;");
		
		TMdbQuery* m_pQuery = m_pDataBase->CreateDBQuery();
		m_pQuery->CloseSQL();
		m_pQuery->SetSQL("insert into numpk_mdb2mdb (pk1, col_num1, col_num2, col_char, col_var, col_date, col_blob) values (seq1.nextval, :col_num1, :col_num2, :col_char, :col_var, :col_date, :col_blob);");
		
		int i = 0;
		int j = 0;
		int iCount = 0;
		int iRound = 0;
		time_t timer;
		int iInt = 0;
		char sChar[32] = {0};
		char sVar[32] = {0};
		
		iInt = CJxlRand::GetRandNum(99999999);
		CJxlRand::GetRandStr(sChar, 30);
		CJxlRand::GetRandStr(sVar, 30);
		
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
			}
			if(iCount >= 9000000)
			{
				iRound++;
				usleep(1000000);
				continue;
			}
			timer = time(NULL);
			printf("Total [%d] records now, begin to insert, ctime: %s\n", iCount, ctime(&timer));
			
			for(i = 0; i<1000000; i++)
			{
				if(i%10000 == 0) 
				{
					m_pQuery->Commit();
					iInt = CJxlRand::GetRandNum(99999999);
					CJxlRand::GetRandStr(sChar, 30);
					CJxlRand::GetRandStr(sVar, 30);
				}
				m_pQuery->SetParameter(0, iInt);
				m_pQuery->SetParameter(1, iInt);
				m_pQuery->SetParameter(2, sChar);
				m_pQuery->SetParameter(3, sChar);
				m_pQuery->SetParameter(4, "20160101000000");
				m_pQuery->SetParameter(5, sVar, 30);
				m_pQuery->Execute();
				usleep(10);
			}
			m_pQuery->Commit();
			iRound++;
		}
		*/
		/*try
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
			m_pQuery->SetSQL("insert into PCC_SESSION (SESSION_ID, USER_NAME, FRAMED_IP_ADDRESS) values (:SESSION_ID, :USER_NAME, :FRAMED_IP_ADDRESS);");
			
			int i = 0;
			char * sBase = "pdsnjkt2-2.smart.com;1469709847;148697554;";
			char sSessionID[64] = {0};
			char sUserName[32] = {0};
			char sIP[32] = {0};
			
			i = 2000000;
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
				CJxlRand::GetRandStr(sUserName, 30);
				CJxlRand::GetRandStr(sIP, 30);
				snprintf(sSessionID, sizeof(sSessionID), "%s%d", sBase, i);
				m_pQuery->SetParameter("SESSION_ID", sSessionID);
				m_pQuery->SetParameter("USER_NAME", sUserName);
				m_pQuery->SetParameter("FRAMED_IP_ADDRESS", sIP);
				m_pQuery->Execute();
				i++;
				usleep(1000);
			}
		}
		catch(TMdbException &e)
		{
			
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
			m_pQuery->SetSQL("insert into NUMPK_MDB2ORA (PK1, COL_NUM1) values (:PK1, :COL_NUM1);");
			
			TMdbQuery* m_pUpdateQuery = m_pDataBase->CreateDBQuery();
			m_pUpdateQuery->CloseSQL();
			m_pUpdateQuery->SetSQL("update NUMPK_MDB2ORA set COL_NUM1 = :COL_NUM1 where PK1=:PK1;");
			int i = 0;
			for(i = 0; i<10000000; i++)
			{
				m_pQuery->SetParameter("PK1", i);
				m_pQuery->SetParameter("COL_NUM1", i);
				m_pQuery->Execute();
				if(i%10000 == 0) 
				{
					if(i %1000 ==0)
					{
						m_pUpdateQuery->SetParameter("PK1", i);
						m_pUpdateQuery->SetParameter("COL_NUM1", -999999);
						m_pUpdateQuery->Execute();
					}
					m_pQuery->Commit();
					m_pUpdateQuery->Commit();
				}
				usleep(10000);
			}
		}
		catch(TMdbException &e)
		{
			
		}
	}
}

