#include "stabilityJob.h"
namespace JxlFrame
{
	CStabilityMOMJob::CStabilityMOMJob()
	{
		
	}
	
	CStabilityMOMJob::~CStabilityMOMJob()
	{
		
	}
	
	void CStabilityMOMJob::insert_test(TMdbQuery * pQuery, const char* sPk1, int iPk2)
	{
		try
		{
			pQuery->SetParameter(0, sPk1);
			pQuery->SetParameter(1, iPk2);
			pQuery->SetParameter(2, iPk2);
			pQuery->SetParameter(3, iPk2);
			pQuery->SetParameter(4, iPk2);
			pQuery->SetParameter(5, iPk2);
			pQuery->Execute();
		}
		catch(TMdbException &e)
		{
			
		}
	}
	
	void CStabilityMOMJob::delete_test(TMdbQuery * pQuery, int iPk2)
	{
		try
		{
			pQuery->SetParameter(0, iPk2);
			pQuery->Execute();
		}
		catch(TMdbException &e)
		{
			
		}
	}
	
	void CStabilityMOMJob::run()
	{
		/*TMdbDatabase* m_pDataBase1, *m_pDataBase2, *m_pDataBase3, *m_pDataBase4;
		TMdbQuery* m_pQuery;
		
		m_pDataBase1 = new(std::nothrow) TMdbDatabase();
		m_pDataBase1->SetLogin("at", "at", "at");
		if(m_pDataBase1->Connect() == false)
		{
			cout << "Connect failed!" << endl;
		}
		m_pDataBase2 = new(std::nothrow) TMdbDatabase();
		m_pDataBase2->SetLogin("at", "at", "at");
		if(m_pDataBase2->Connect() == false)
		{
			cout << "Connect failed!" << endl;
		}
		m_pDataBase3 = new(std::nothrow) TMdbDatabase();
		m_pDataBase3->SetLogin("jxl", "jxl", "jxl");
		if(m_pDataBase3->Connect() == false)
		{
			cout << "Connect failed!" << endl;
		}
		m_pDataBase4 = new(std::nothrow) TMdbDatabase();
		m_pDataBase4->SetLogin("jxl", "jxl", "jxl");
		if(m_pDataBase4->Connect() == false)
		{
			cout << "Connect failed!" << endl;
		}
		getchar();
		getchar();
		sleep(1000);*/
		/*
		char pk1_base[] = "0000000000000000000000";
		char sPk1[128] = {0};
		int iPk1[10000] = {0};
		
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
			
			m_pQuery->SetSQL("delete from varchar_test where 1;");
			m_pQuery->Execute();
			m_pQuery->Commit();
			m_pQuery->Close();
			m_pQuery->SetSQL("insert into varchar_test (pk1) values (:pk1);");
			
			int i = 0;
			time_t timer = time(NULL);
			printf("ctime: %s\n", ctime(&timer));
			for(i = 0; i<5000000; i++)
			{
				if(i!=0 && i%10000 == 0) m_pQuery->Commit();
				snprintf(sPk1, sizeof(sPk1), "%s%d", pk1_base, i);
				m_pQuery->SetParameter(0, sPk1);
				m_pQuery->Execute();
			}
			m_pQuery->Commit();
			timer = time(NULL);
			printf("ctime: %s\n", ctime(&timer));
			
			TMdbQuery* m_pInstQuery = m_pDataBase->CreateDBQuery();
			m_pInstQuery->CloseSQL();
			m_pInstQuery->SetSQL("insert into varchar_test (pk1) values (:pk1);");
			
			TMdbQuery* m_pDelQuery = m_pDataBase->CreateDBQuery();
			m_pDelQuery->CloseSQL();
			m_pDelQuery->SetSQL("delete from varchar_test where pk1 = :pk1;");
			
			TMdbQuery* m_pSelQuery = m_pDataBase->CreateDBQuery();
			m_pSelQuery->CloseSQL();
			m_pSelQuery->SetSQL("select * from varchar_test where pk1 = :pk1;");
			bool bExist = false;
			while(1)
			{
				for(i = 0; i<10000; i++)
				{
					while(1)
					{
						bExist = false;
						iPk1[i] = CJxlRand::GetRandNum(4999999);
						//printf("iPk1[i] = [%d]\n", iPk1[i]);
						snprintf(sPk1, sizeof(sPk1), "%s%d", pk1_base, iPk1[i]);
						m_pSelQuery->SetParameter(0, sPk1);
						m_pSelQuery->Open();
						while(m_pSelQuery->Next())
						{
							bExist = true;
						}
						if(bExist)
						{
							m_pDelQuery->SetParameter(0, sPk1);
							m_pDelQuery->Execute();
							break;
						}
						else
						{
							continue;
						}
					}
				}
				m_pDelQuery->Commit();
				
				for(i = 9999; i>= 0; i--)
				{
					snprintf(sPk1, sizeof(sPk1), "%s%d", pk1_base, iPk1[i]);
					m_pInstQuery->SetParameter(0, sPk1);
					m_pInstQuery->Execute();
				}
				m_pInstQuery->Commit();
				usleep(1000);
			}
		}
		catch(TMdbException &e)
		{
			
		}
		*/
		/*
		char pk1_base[] = "adsfadlkl;kghplakd;ljgoi;werpsa[kgk;kjsa;kldkfjlkwerjhg;lka;ldgj;okerjgh;klajsd;klfj;oiwerhg;lkajef;hwero;gj;akjreg;kojre;odksd";
		char sPk1[128] = {0};
		int iPk2 = 0;
		
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
			
			TMdbQuery* m_pInstQuery = m_pDataBase->CreateDBQuery();
			m_pInstQuery->CloseSQL();
			m_pInstQuery->SetSQL("insert into RESERVE_BAL (SESSION_ID, BAL_ID, ACCT_ID, BAL_SHARE_ID, USED_BAL, RESERVE_BAL, UPDATE_DATE) values (:SESSION_ID, :BAL_ID, :ACCT_ID, :BAL_SHARE_ID, :USED_BAL, :RESERVE_BAL, sysdate);");
			
			TMdbQuery* m_pDelQuery = m_pDataBase->CreateDBQuery();
			m_pDelQuery->CloseSQL();
			m_pDelQuery->SetSQL("delete from RESERVE_BAL where BAL_ID = :BAL_ID;");
			
			while(1)
			{
				for(int i = 0; i<1000; i++)
				{
					delete_test(m_pDelQuery, CJxlRand::GetRandNum(9999999));
					iPk2 = CJxlRand::GetRandNum(9999999);
					snprintf(sPk1, CJxlRand::GetRandNum(75, 115), "%s", pk1_base);
					snprintf(sPk1+strlen(sPk1), sizeof(sPk1) - strlen(sPk1), "%d", iPk2);
					insert_test(m_pInstQuery, sPk1, iPk2);
				}
				m_pDelQuery->Commit();
				usleep(1000);
			}
		}
		catch(TMdbException &e)
		{
			
		}*/
		
		/*
		char * m_sUser = "jxl";
		char * m_sPassword = "jxl";
		char * m_sDsn = "jxl";
		
		char sValue[8196] = {'0'};
		
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
			m_pQuery->SetSQL("select * from numpk_mdb2mdb where col_char=:col_char;");
			m_pQuery->SetParameter(0, sValue);
			m_pQuery->Open();
			while(m_pQuery->Next())
			{
				printf("bingo\n");
			}
		}
		catch(TMdbException &e)
		{
			
		}
		*/
		
		printf("TEST START.\n");
		
		char * m_sUser = "qmdb12aix";
		char * m_sPassword = "smart";
		char * m_sDsn = "pcc";
		
		try
		{
			TMDBDBInterface* m_pDBLink;   //����
    		TMDBDBQueryInterface*    m_pOraQuery;    //����
			m_pDBLink = TMDBDBFactory::CeatDB();
	        m_pDBLink->SetLogin(m_sUser, m_sPassword, m_sDsn);
	        bFlag = m_pDBLink->Connect();
	        m_pOraQuery = m_pDBLink->CreateDBQuery();
	        m_pOraQuery->Close();
			m_pOraQuery->SetSQL("insert into jxl_test_2 (pk1, col_num1) values (:pk1, :col_num1);");
	        m_pOraQuery->SetParameter("pk1" ,1);
	        m_pOraQuery->SetParameter("col_num1" ,999999999999999999);
	        m_pOraQuery->Execute();
	        m_pOraQuery->Commit();
		}
		catch(TMDBDBExcpInterface &oe)
	    {
	        printf("TDBException:%s\n",oe.GetErrMsg());
	        printf("QuerySQL:\n%s\n",oe.GetErrSql());
	    }
	}
}

