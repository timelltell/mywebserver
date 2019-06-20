
#include "CountDownLatch.h"
//既可以用于主线程向所有子线程发起起跑，也可以用于所有子线程准备完毕后主线程才开始工作
CountDownLatch::CountDownLatch(int count)
  : mutex_(),
    condition_(mutex_),//初始化条件变量
    count_(count)//初始化计数器
{ }

void CountDownLatch::wait()//执行条件变量等待过程
{
    MutexLockGuard lock(mutex_);
    while (count_ > 0)
        condition_.wait();
}

void CountDownLatch::countDown()//计数器减1
{
    MutexLockGuard lock(mutex_);
    --count_;
    if (count_ == 0)
        condition_.notifyAll();
}