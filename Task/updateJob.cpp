#include "updateJob.h"
namespace JxlFrame
{
	CUpdateJob::CUpdateJob()
	{
		
	}
	
	CUpdateJob::~CUpdateJob()
	{
		
	}
	
	void CUpdateJob::run()
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
		
		TMdbQuery* m_pPkSelQuery = m_pDataBase->CreateDBQuery();
		m_pPkSelQuery->CloseSQL();
		m_pPkSelQuery->SetSQL("select MAX(pk1) from numpk_mdb2mdb;");
		
		TMdbQuery* m_pSelQuery = m_pDataBase->CreateDBQuery();
		m_pSelQuery->CloseSQL();
		m_pSelQuery->SetSQL("select pk1 from numpk_mdb2mdb where pk1<:pk1 limit 100;");
		
		TMdbQuery* m_pQuery = m_pDataBase->CreateDBQuery();
		m_pQuery->CloseSQL();
		m_pQuery->SetSQL("update numpk_mdb2mdb set col_num1 = :col_num1, col_num2 = :col_num2, col_char = :col_char, col_var = :col_var, col_blob = :col_blob where pk1 = :pk1;");
		
		int iCount = 0;
		int iMaxPk = 0;
		int iPk = 0;
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
			if(iCount %100000 == 0)
			{
				m_pPkSelQuery->Open();
				while(m_pPkSelQuery->Next())
				{
					iMaxPk = m_pPkSelQuery->Field(0).AsInteger();
				}
			}
			
			iInt = CJxlRand::GetRandNum(99999999);
			CJxlRand::GetRandStr(sChar, 30);
			CJxlRand::GetRandStr(sVar, 30);
				
			m_pSelQuery->SetParameter(0, CJxlRand::GetRandNum(iMaxPk));
			m_pSelQuery->Open();
			while(m_pSelQuery->Next())
			{
				iPk = m_pSelQuery->Field(0).AsInteger();
				m_pQuery->SetParameter(0, iInt);
				m_pQuery->SetParameter(1, iInt);
				m_pQuery->SetParameter(2, sChar);
				m_pQuery->SetParameter(3, sChar);
				m_pQuery->SetParameter(4, sVar, 30);
				m_pQuery->SetParameter(5, iPk);
				m_pQuery->Execute();
			}
			m_pQuery->Commit();
			iCount++;
			usleep(10000);
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
			m_pQuery->SetSQL("update PCC_SESSION set USER_ID=:USER_ID, USER_NAME=:USER_NAME, SERV_BEGIN_TIME=:SERV_BEGIN_TIME, RESERVE_TIMES=:RESERVE_TIMES, EXP_TIME=:EXP_TIME, WORK_GROUP_ID=:WORK_GROUP_ID, PID_INFO=:PID_INFO, ORIGIN_HOST=:ORIGIN_HOST, ORIGIN_REALM=:ORIGIN_REALM, RULE_ID_LIST=:RULE_ID_LIST, EXT_ATTR=:EXT_ATTR, USED_UNIT=:USED_UNIT, USED_ATTR_ID=:USED_ATTR_ID, TOL_RULE_ID_LIST=:TOL_RULE_ID_LIST, PCR_EVENT_ID=:PCR_EVENT_ID, FRAMED_IP_ADDRESS=:FRAMED_IP_ADDRESS, BAL_ID1=:BAL_ID1, ACCT_RES_ID1=:ACCT_RES_ID1, RESERVE_BAL1=:RESERVE_BAL1, BAL_ID2=:BAL_ID2, ACCT_RES_ID2=:ACCT_RES_ID2, RESERVE_BAL2=:RESERVE_BAL2, BAL_ID3=:BAL_ID3, ACCT_RES_ID3=:ACCT_RES_ID3, RESERVE_BAL3=:RESERVE_BAL3, BAL_ID4=:BAL_ID4, ACCT_RES_ID4=:ACCT_RES_ID4, RESERVE_BAL4=:RESERVE_BAL4 where SESSION_ID=:SESSION_ID;");
			
			int i = 0;
			
			char sUserName[32] = {0};
			char * sBase = "pdsnjkt2-2.smart.com;1469709847;148697554;";
			char sSessionID[64] = {0};
			char sIP[32] = {0};
			
			i = 1000000;
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
				m_pQuery->SetParameter("USER_ID",12345);
				m_pQuery->SetParameter("USER_NAME",sUserName);
				m_pQuery->SetParameter("SERV_BEGIN_TIME","20160908100000");
				m_pQuery->SetParameter("RESERVE_TIMES",12345);
				m_pQuery->SetParameter("EXP_TIME","20160908100000");
				m_pQuery->SetParameter("WORK_GROUP_ID",12345);
				m_pQuery->SetParameter("PID_INFO","180,176,333|10.17.130.65");
				m_pQuery->SetParameter("ORIGIN_HOST","pdsnjkt2-1.smart.com");
				m_pQuery->SetParameter("ORIGIN_REALM","smart.com");
				m_pQuery->SetParameter("RULE_ID_LIST","#52,352,133,P2P_ALL,341,341,1,-1,20150929150744,20360207132815,1,Unified Prepaid Social Default,66#52,351,129,Volum Base,0,216,3,-1,20150929150744,20300101000000,4,Unified Prepaid Social Default,66");
				m_pQuery->SetParameter("EXT_ATTR","20160728210201##$#$$$$$16777238$$$$20160728210201$$$275=0;288=$$290=20160728194423$$$315360000$$572=0,571=0,570=0,573=0$15=0$0,1,2,3,4,11,15,16,18,19,20,21,22,23,24,26,17,$45=10.18.36.117;265=297004B331A4;63=0;42=2001;224=510091199071273;40=4;584=3678706821$192$$$,52");
				m_pQuery->SetParameter("USED_UNIT",12345);
				m_pQuery->SetParameter("USED_ATTR_ID",12345);
				m_pQuery->SetParameter("TOL_RULE_ID_LIST","");
				m_pQuery->SetParameter("PCR_EVENT_ID",12345);
				m_pQuery->SetParameter("FRAMED_IP_ADDRESS",sIP);
				m_pQuery->SetParameter("BAL_ID1",12345);
				m_pQuery->SetParameter("ACCT_RES_ID1",12345);
				m_pQuery->SetParameter("RESERVE_BAL1",12345);
				m_pQuery->SetParameter("BAL_ID2",12345);
				m_pQuery->SetParameter("ACCT_RES_ID2",12345);
				m_pQuery->SetParameter("RESERVE_BAL2",12345);
				m_pQuery->SetParameter("BAL_ID3",12345);
				m_pQuery->SetParameter("ACCT_RES_ID3",12345);
				m_pQuery->SetParameter("RESERVE_BAL3",12345);
				m_pQuery->SetParameter("BAL_ID4",12345);
				m_pQuery->SetParameter("ACCT_RES_ID4",12345);
				m_pQuery->SetParameter("RESERVE_BAL4",12345);
				m_pQuery->Execute();
				
				
				CJxlRand::GetRandStr(sUserName, 30);
				CJxlRand::GetRandStr(sIP, 30);
				m_pQuery->SetParameter("SESSION_ID", sSessionID);
				m_pQuery->SetParameter("USER_ID",12345);
				m_pQuery->SetParameter("USER_NAME",sUserName);
				m_pQuery->SetParameter("SERV_BEGIN_TIME","20160908100000");
				m_pQuery->SetParameter("RESERVE_TIMES",12345);
				m_pQuery->SetParameter("EXP_TIME","20160908100000");
				m_pQuery->SetParameter("WORK_GROUP_ID",12345);
				m_pQuery->SetParameter("PID_INFO","180,176,333|10.17.130.65");
				m_pQuery->SetParameter("ORIGIN_HOST","pdsnjkt2-1.smart.com");
				m_pQuery->SetParameter("ORIGIN_REALM","smart.com");
				m_pQuery->SetParameter("RULE_ID_LIST","#52,352,133,P2P_ALL,341,341,1,-1,20150929150744,20360207132815,1,Unified Prepaid Social Default,66#52,351,129,Volum Base,0,216,3,-1,20150929150744,20300101000000,4,Unified Prepaid Social Default,66");
				m_pQuery->SetParameter("EXT_ATTR","20160728210201##$#$$$$$16777238$$$$20160728210201$$$275=0;288=$$290=20160728194423$$$315360000$$572=0,571=0,570=0,573=0$15=0$0,1,2,3,4,11,15,16,18,19,20,21,22,23,24,26,17,$45=10.18.36.117;265=297004B331A4;63=0;42=2001;224=510091199071273;40=4;584=3678706821$192$$$,52");
				m_pQuery->SetParameter("USED_UNIT",12345);
				m_pQuery->SetParameter("USED_ATTR_ID",12345);
				m_pQuery->SetParameter("TOL_RULE_ID_LIST","");
				m_pQuery->SetParameter("PCR_EVENT_ID",12345);
				m_pQuery->SetParameter("FRAMED_IP_ADDRESS",sIP);
				m_pQuery->SetParameter("BAL_ID1",12345);
				m_pQuery->SetParameter("ACCT_RES_ID1",12345);
				m_pQuery->SetParameter("RESERVE_BAL1",12345);
				m_pQuery->SetParameter("BAL_ID2",12345);
				m_pQuery->SetParameter("ACCT_RES_ID2",12345);
				m_pQuery->SetParameter("RESERVE_BAL2",12345);
				m_pQuery->SetParameter("BAL_ID3",12345);
				m_pQuery->SetParameter("ACCT_RES_ID3",12345);
				m_pQuery->SetParameter("RESERVE_BAL3",12345);
				m_pQuery->SetParameter("BAL_ID4",12345);
				m_pQuery->SetParameter("ACCT_RES_ID4",12345);
				m_pQuery->SetParameter("RESERVE_BAL4",12345);
				m_pQuery->Execute();
				i++;
				usleep(500);
			}
		}
		catch(TMdbException &e)
		{
			
		}
	}
}

