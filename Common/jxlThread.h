#ifndef _JXLTHREAD_H__
#define _JXLTHREAD_H__

#include "jxlOS.h"

//#include <unistd.h>

//using namespace JxlFrame
using namespace std;
namespace JxlFrame
{
	class CJxlThread
	{
	private:
	    //当前线程的线程ID
	    pthread_t m_tid;
	    //线程的状态
	    int m_threadStatus;
	    //线程属性
	    pthread_attr_t m_attr;
	    //线程优先级
	    sched_param m_param;
	    //获取执行方法的指针
	    static void* run0(void* pVoid);
	    //内部执行方法
	    void* run1();
	
	public:
	    //线程的状态－新建
	    static const int THREAD_STATUS_NEW = 0;
	    //线程的状态－正在运行
	    static const int THREAD_STATUS_RUNNING = 1;
	    //线程的状态－运行结束
	    static const int THREAD_STATUS_EXIT = -1;
	    //构造函数
	    CJxlThread();
	    //析构
	    virtual ~CJxlThread();
	    //线程的运行实体
	    virtual void run() = 0;
	    //开始执行线程
	    bool start();
	    //获取线程状态
	    int getState();
	    //等待线程直至退出
	    void join();
	    //等待线程退出或者超时
	    void join(unsigned long millisTime);
	    //获取This线程ID
	    pthread_t getThreadID();
	    //获取当前线程ID
	    static pthread_t getCurrentThreadID();
	    //当前线程是否和某个线程相等,通过 tid 判断
	    static bool isEquals(CJxlThread *iTarget);
	    //设置线程的类型:绑定/非绑定
	    void setThreadScope(bool isSystem);
	    //获取线程的类型:绑定/非绑定
	    bool getThreadScope();
	    //设置线程的优先级,1-99,其中99为实时;意外的为普通
	    void setThreadPriority(int priority);
	    //获取线程的优先级
	    int getThreadPriority();
	};
}

#endif /* _JXLTHREAD_H__ */
