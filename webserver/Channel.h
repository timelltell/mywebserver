#pragma once

#include "Timer.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <sys/epoll.h>
#include <functional>
#include <sys/epoll.h>

class EventLoop;
class HttpData;

class Channel
{
private:
	typedef std::function<void()> CallBack;
	EventLoop *loop_;
	int fd_;
	__uint32_t events_;
	__uint32_t revents_;
	__uint32_t lastEvents_;
	// 方便找到上层持有该Channel的对象
	std::weak_ptr<HttpData> holder_;
private:
	CallBack readHandler_;
	CallBack writeHandler_;
	CallBack errorHandler_;
	CallBack connHandler_;
public:
	Channel(EventLoop *loop);
	Channel(EventLoop *loop, int fd);
	~Channel();
	int getFd();
	void setFd(int fd);
	void setHolder(std::shared_ptr<HttpData> holder)
	{
		holder_ = holder;
	}
	std::shared_ptr<HttpData> getHolder()
	{
		std::shared_ptr<HttpData> ret(holder_.lock());//weak_ptr.lock() 会把weak_ptr提升为一个 shared_ptr 对象，当 引用计数为0 ，那么 shared_ptr 为空
		return ret;
	}
	void setReadHandler(CallBack &&readHandler)
	{
		readHandler_ = readHandler;
	}
	void setWriteHandler(CallBack &&writeHandler)
	{
		writeHandler_ = writeHandler;
	}
	void setErrorHandler(CallBack &&errorHandler)
	{
		errorHandler_ = errorHandler;
	}
	void setConnHandler(CallBack &&connHandler)
	{
		connHandler_ = connHandler;
	}

	void handleEvents()
	{
		events_ = 0;
		if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
		{
			events_ = 0;
			return;
		}
		if (revents_ & EPOLLERR)
		{
			if (errorHandler_) errorHandler_();
			events_ = 0;
			return;
		}
		if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
		{
			handleRead();
		}
		if (revents_ & EPOLLOUT)
		{
			handleWrite();
		}
		handleConn();
	}
	void handleRead();
	void handleWrite();
	void handleConn();


	void setRevents(__uint32_t ev)
	{
		revents_ = ev;
	}
	void setEvents(__uint32_t ev)
	{
		events_ = ev;
	}
	__uint32_t& getEvents()
	{
		return events_;
	}
	bool EqualAndUpdateLastEvents()
	{
		bool ret = (lastEvents_ == events_);
		lastEvents_ = events_;
		return ret;
	}
	__uint32_t getLastEvents()
	{
		return lastEvents_;
	}
};
typedef std::shared_ptr<Channel> SP_Channel;
