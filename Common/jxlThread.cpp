#include "jxlThread.h"
namespace JxlFrame
{
	void* CJxlThread::run0(void* pVoid)
	{
	    CJxlThread* p = (CJxlThread*) pVoid;
	    p->run1();
	    return p;
	}
	
	void* CJxlThread::run1()
	{
	
	    m_threadStatus = THREAD_STATUS_RUNNING;
	    m_tid = pthread_self();
	    run();
	    m_threadStatus = THREAD_STATUS_EXIT;
	    m_tid = 0;
	    pthread_exit(NULL);
		return NULL;
	}
			
	CJxlThread::CJxlThread()
	{
	    m_tid = 0;
	    m_threadStatus = THREAD_STATUS_NEW;
	    pthread_attr_init(&m_attr);
	}
	
	CJxlThread::~CJxlThread()
	{
	    pthread_attr_destroy(&m_attr);
	}
	
	bool CJxlThread::start()
	{
	    return pthread_create(&m_tid, &m_attr, run0, this) == 0;
	}
	
	pthread_t CJxlThread::getCurrentThreadID()
	{
	    return pthread_self();
	}
	
	pthread_t CJxlThread::getThreadID()
	{
	    return m_tid;
	}
	
	int CJxlThread::getState()
	{
	    return m_threadStatus;
	}
	
	void CJxlThread::join()
	{
	    if (m_tid > 0)
	    {
	        pthread_join(m_tid, NULL);
	    }
	}
	
	void CJxlThread::join(unsigned long millisTime)
	{
	
	    if (m_tid == 0)
	    {
	        return;
	    }
	    if (millisTime == 0)
	    {
	        join();
	    }else
	    {
	        unsigned long k = 0;
	        while (m_threadStatus != THREAD_STATUS_EXIT && k <= millisTime)
	        {
	            usleep(100);
	            k++;
	        }
	    }
	}
	
	bool CJxlThread::isEquals(CJxlThread *iTarget)
	{
	    if (iTarget == NULL)
	    {
	        return false;
	    }
	    return pthread_self() == iTarget->m_tid;
	}
	
	void CJxlThread::setThreadScope(bool isSystem)
	{
	    if (isSystem)
	    {
	        pthread_attr_setscope(&m_attr, PTHREAD_SCOPE_SYSTEM);
	    }else
	    {
	        pthread_attr_setscope(&m_attr, PTHREAD_SCOPE_PROCESS);
	    }
	}
	
	bool CJxlThread::getThreadScope()
	{
	    int scopeType = 0;
	    pthread_attr_getscope(&m_attr, &scopeType);
	    return scopeType == PTHREAD_SCOPE_SYSTEM;
	}
	
	void CJxlThread::setThreadPriority(int priority)
	{
	    /*pthread_attr_getschedparam(&m_attr, &m_param);
	    m_param.__sched_priority = priority;
	    pthread_attr_setschedparam(&m_attr, &m_param);*/
	}
	
	int CJxlThread::getThreadPriority()
	{
	    /*pthread_attr_getschedparam(&m_attr, &m_param);
	    return m_param.__sched_priority;*/
	}

}
