
#include "Logging.h"
#include "CurrentThread.h"
#include "Thread.h"
#include "AsyncLogging.h"
#include <assert.h>
#include <iostream>
#include <time.h>  
#include <sys/time.h> 


static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
static AsyncLogging *AsyncLogger_;

std::string Logger::logFileName_ = "/chenbin_WebServer.log";

void once_init()
{
    AsyncLogger_ = new AsyncLogging(Logger::getLogFileName());
    AsyncLogger_->start(); 
}

void output(const char* msg, int len)
{
	//�ڶ��̻߳����У���Щ�½���Ҫִ��һ�Ρ�ͨ������ʼ��Ӧ�ó���ʱ�����ԱȽ����׵ؽ������main�����С�������дһ����ʱ���Ͳ�����main�����ʼ���ˣ�������þ�̬��ʼ������ʹ��һ�γ�ʼ����pthread_once����Ƚ�����Щ��
	//	int pthread_once(pthread_once_t *once_control, void(*init_routine) (void))��
	//	���ܣ�������ʹ�ó�ֵΪPTHREAD_ONCE_INIT��once_control������֤init_routine()�����ڱ�����ִ�������н�ִ��һ�Ρ�
	//	�ڶ��̱߳�̻����£�����pthread_once()���û�����ڶ���߳��У�init_routine()������ִ��һ�Σ��������ĸ��߳���ִ���ǲ����ģ������ں˵�����������
	//	Linux Threadsʹ�û�����������������֤��pthread_once()ָ���ĺ���ִ���ҽ�ִ��һ�Σ���once_control��ʾ�Ƿ�ִ�й���
	//	���once_control�ĳ�ֵ����PTHREAD_ONCE_INIT��Linux Threads����Ϊ0����pthread_once() ����Ϊ�ͻ᲻������
    pthread_once(&once_control_, once_init);
    AsyncLogger_->append(msg, len);
}

Logger::Impl::Impl(const char *fileName, int line)
  : stream_(),
    line_(line),
    basename_(fileName)
{
    formatTime();
}

void Logger::Impl::formatTime()
{
    struct timeval tv;
    time_t time;
    char str_t[26] = {0};
    gettimeofday (&tv, NULL);
    time = tv.tv_sec;
    struct tm* p_time = localtime(&time);   
    strftime(str_t, 26, "%Y-%m-%d %H:%M:%S\n", p_time);
    stream_ << str_t;
}

Logger::Logger(const char *fileName, int line)
  : impl_(fileName, line)
{ }

Logger::~Logger()
{
    impl_.stream_ << " -- " << impl_.basename_ << ':' << impl_.line_ << '\n';
    const LogStream::Buffer& buf(stream().buffer());
    output(buf.data(), buf.length());
}