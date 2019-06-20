
#include "CountDownLatch.h"
//�ȿ����������߳����������̷߳������ܣ�Ҳ���������������߳�׼����Ϻ����̲߳ſ�ʼ����
CountDownLatch::CountDownLatch(int count)
  : mutex_(),
    condition_(mutex_),//��ʼ����������
    count_(count)//��ʼ��������
{ }

void CountDownLatch::wait()//ִ�����������ȴ�����
{
    MutexLockGuard lock(mutex_);
    while (count_ > 0)
        condition_.wait();
}

void CountDownLatch::countDown()//��������1
{
    MutexLockGuard lock(mutex_);
    --count_;
    if (count_ == 0)
        condition_.notifyAll();
}