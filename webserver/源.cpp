//#pragma once
//#include "Timer.h"
//#include "base/CountDownLatch.h"
//#include <getopt.h>
//#include <string>
//#include <vector>
//#include <memory>
//#include <functional>
//#include <sys/epoll.h>
//#include <errno.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <string.h>
//#include <queue>
//#include <deque>
//#include <assert.h>
//#include <arpa/inet.h>
//#include <sys/eventfd.h>
//#include <iostream>
//#include "base/CurrentThread.h"
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/prctl.h>
//#include <signal.h>
//#include <errno.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netinet/tcp.h>
//#include <sys/epoll.h>
//using namespace std;
//ssize_t readn(int fd, void *buff, size_t n)
//{
//	size_t nleft = n;
//	ssize_t nread = 0;
//	ssize_t readSum = 0;
//	char *ptr = (char*)buff;
//	while (nleft > 0)
//	{
//		if ((nread = read(fd, ptr, nleft)) < 0)
//		{
//			if (errno == EINTR)
//				nread = 0;
//			else if (errno == EAGAIN)
//			{
//				return readSum;
//			}
//			else
//			{
//				return -1;
//			}
//		}
//		else if (nread == 0)
//			break;
//		readSum += nread;
//		nleft -= nread;
//		ptr += nread;
//	}
//	return readSum;
//}
//int socket_bind_listen(int port) {
//	if (port < 0 || port > 65535)
//	{
//		return -1;
//	}
//	int listen_fd = 0;
//	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//		return -1;
//	}
//	int optval = 1;
//	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
//		return -1;
//	}
//	struct sockaddr_in server_sockaddr;
//	bzero((char*)&server_sockaddr, sizeof(server_sockaddr));
//	server_sockaddr.sin_family = AF_INET;
//	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	server_sockaddr.sin_port = htons((unsigned short)port);
//	if (bind(listen_fd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1) {
//		return -1;
//	}
//	if (listen(listen_fd, 2048) == -1)
//		return -1;
//	if (listen_fd == -1)
//	{
//		close(listen_fd);
//		return -1;
//	}
//	return listen_fd;
//}
//void handle_for_sigpipe()
//{
//	struct sigaction sa;
//	memset(&sa, '\0', sizeof(sa));
//	sa.sa_handler = SIG_IGN;
//	sa.sa_flags = 0;
//	if (sigaction(SIGPIPE, &sa, NULL))
//		return;
//}
//int setSocketNonBlocking(int fd)
//{
//	int flag = fcntl(fd, F_GETFL, 0);
//	if (flag == -1)
//		return -1;
//
//	flag |= O_NONBLOCK;
//	if (fcntl(fd, F_SETFL, flag) == -1)
//		return -1;
//	return 0;
//}
//ssize_t writen(int fd, void *buff, size_t n)
//{
//	size_t nleft = n;
//	ssize_t nwritten = 0;
//	ssize_t writeSum = 0;
//	char *ptr = (char*)buff;
//	while (nleft > 0)
//	{
//		if ((nwritten = write(fd, ptr, nleft)) <= 0)
//		{
//			if (nwritten < 0)
//			{
//				if (errno == EINTR)
//				{
//					nwritten = 0;
//					continue;
//				}
//				else if (errno == EAGAIN)
//				{
//					return writeSum;
//				}
//				else
//					return -1;
//			}
//		}
//		writeSum += nwritten;
//		nleft -= nwritten;
//		ptr += nwritten;
//	}
//	return writeSum;
//}
//class EventLoop;
//class HttpData;
//class Channel;
//const int EVENTSNUM = 4096;
//typedef std::shared_ptr<Channel> SP_Channel;
//class Epoll {
//public:
//	Epoll();
//	~Epoll();
//	int epollFd_;
//	std::vector<epoll_event> events_;
//	void epoll_add(SP_Channel request, int timeout);
//	void epoll_mod(SP_Channel request, int timeout);
//	void epoll_del(SP_Channel request);
//	static const int MAXFDS = 100000;
//	std::shared_ptr<Channel> fd2chan_[MAXFDS];
//	std::shared_ptr<HttpData> fd2http_[MAXFDS];
//	std::vector<SP_Channel> poll();
//	std::vector<SP_Channel> getEventsRequest(int events_num);
//	TimerManager timerManager_;
//	void handleExpired();
//
//};
//void Epoll::epoll_add(SP_Channel request, int timeout) {
//	int fd = request->getFd();
//	struct epoll_event events;
//	events.data.fd = fd;
//	events.events = request->getEvents();
//	request->EqualAndUpdateLastEvents();
//	fd2chan_[fd] = request;
//	if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &events) < 0) {
//		fd2chan_[fd].reset();
//	}
//}
//void Epoll::epoll_mod(SP_Channel request, int timeout) {
//	int fd = request->getFd();
//	struct epoll_event events;
//	events.data.fd = fd;
//	events.events = request->getEvents();
//	if (epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &events) < 0) {
//		fd2chan_[fd].reset();
//	}
//}
//void Epoll::epoll_del(SP_Channel request) {
//	int fd = request->getFd();
//	struct epoll_event event;
//	event.data.fd = fd;
//	event.events = request->getLastEvents();
//	if (epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, &event) < 0) {
//	}
//	fd2chan_[fd].reset();
//	fd2http_[fd].reset();
//}
//Epoll::Epoll() :
//	epollFd_(epoll_create1(EPOLL_CLOEXEC)),
//	events_(EVENTSNUM)
//{
//	assert(epollFd_ > 0);
//}
//void Epoll::handleExpired()
//{
//	timerManager_.handleExpiredEvent();
//}
//const int EPOLLWAIT_TIME = 10000;
//
//std::vector<SP_Channel> Epoll::poll() {
//	while (true) {
//		int event_count = epoll_wait(epollFd_, &*events_.begin(), events_.size(), EPOLLWAIT_TIME);
//		if (event_count < 0) {}
//		std::vector<SP_Channel> req_data = getEventsRequest(event_count);
//		if (req_data.size() > 0) return req_data;
//	}
//}
//std::vector<SP_Channel> Epoll::getEventsRequest(int events_num)
//{
//	std::vector<SP_Channel> req_data;
//	for (int i = 0; i < events_num; i++) {
//		int fd = events_[i].data.fd;
//		SP_Channel cur_req = fd2chan_[fd];
//		if (cur_req) {
//			cur_req->setRevents(events_[i].events);
//			cur_req->setEvents(0);
//			req_data.push_back(cur_req);
//		}
//	}
//	return req_data;
//}
//
//int createEventfd()
//{
//	int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
//	if (evtfd < 0)
//	{
//		abort();
//	}
//	return evtfd;
//}
//
//class EventLoop {
//public:
//	EventLoop();
//	~EventLoop();
//	typedef std::function<void()> Functor;
//	bool looping;
//	bool quit_;
//	bool callingPendingFunctors_;
//	bool eventHandling_;
//	mutable MutexLock mutex_;
//	int wakeupFd_;
//	EventLoop *t_loopInThisThread;
//	shared_ptr<Epoll> poller_;
//	const pid_t threadId_;
//	vector<Functor> pendingFunctors_;
//	shared_ptr<Channel> pwakeupChannel_;
//	void handleRead();
//	void handleConn();
//	void removeFromPoller(shared_ptr<Channel> channel)
//	{
//		//shutDownWR(channel->getFd());
//		poller_->epoll_del(channel);
//	}
//	void updatePoller(shared_ptr<Channel> channel, int timeout = 0)
//	{
//		poller_->epoll_mod(channel, timeout);
//	}
//	void addToPoller(shared_ptr<Channel> channel, int timeout = 0)
//	{
//		poller_->epoll_add(channel, timeout);
//	}
//	void assertInLoopThread()
//	{
//		assert(isInLoopThread());
//	}
//	bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
//	void quit();
//	void wakeup();
//	void loop();
//	void doPendingFunctors();
//
//};
//
//EventLoop::EventLoop()
//	:looping(false),
//	callingPendingFunctors_(false),
//	quit_(false),
//	poller_(new Epoll()),
//	threadId_(CurrentThread::tid()),
//	wakeupFd_(createEventfd()),
//	pwakeupChannel_(new Channel(this, wakeupFd_))
//{
//	if (t_loopInThisThread) {}
//	else {
//		t_loopInThisThread = this;
//	}
//	pwakeupChannel_->setEvents(EPOLLIN | EPOLLET);
//	pwakeupChannel_->setReadHandler(bind(&EventLoop::handleRead, this));
//	pwakeupChannel_->setConnHandler(bind(&EventLoop::handleConn, this));
//	poller_->epoll_add(pwakeupChannel_, 0);
//}
//EventLoop::~EventLoop()
//{
//	close(wakeupFd_);
//	t_loopInThisThread = NULL;
//
//}
//void EventLoop::handleRead() {
//	uint64_t one = 1;
//	ssize_t n = readn(wakeupFd_, &one, sizeof one);
//
//	pwakeupChannel_->setEvents(EPOLLIN | EPOLLET);
//}
//void EventLoop::handleConn() {
//	updatePoller(pwakeupChannel_, 0);
//}
//void EventLoop::wakeup()
//{
//	uint64_t one = 1;
//	ssize_t n = writen(wakeupFd_, (char*)(&one), sizeof one);
//	if (n != sizeof one)
//	{
//	}
//}
//void EventLoop::quit()
//{
//	quit_ = true;
//	if (!isInLoopThread())
//	{
//		wakeup();
//	}
//}
//void EventLoop::loop() {
//	assert(!looping);
//	assert(isInLoopThread());
//	looping = true;
//	quit_ = false;
//	std::vector<SP_Channel> ret;
//	while (!quit) {
//		ret.clear();
//		ret = poller_->poll();
//		eventHandling_ = true;
//		for (auto &it : ret) {
//			it->handleEvents();
//		}
//		eventHandling_ = false;
//		doPendingFunctors();
//		poller_->handleExpired();
//	}
//	looping = false;
//}
//typedef std::function<void()> Functor;
//
//void EventLoop::doPendingFunctors() {
//	std::vector<Functor> functors;
//	callingPendingFunctors_ = true;
//	{
//		MutexLockGuard lock(mutex_);
//		functors.swap(pendingFunctors_);
//	}
//	for (size_t i = 0; i < functors.size(); ++i)
//		functors[i]();
//	callingPendingFunctors_ = false;
//}
//
//class Channel {
//public:
//	Channel(EventLoop *loop, int fd);
//	Channel(EventLoop *loop);
//	typedef std::function<void()> CallBack;
//	CallBack readHandler_;
//	CallBack writeHandler_;
//	CallBack errorHandler_;
//	CallBack connHandler_;
//	EventLoop *loop_;
//	int fd_;
//	__uint32_t events_;
//	__uint32_t revents_;
//	__uint32_t lastEvents_;
//	// 方便找到上层持有该Channel的对象
//	//std::weak_ptr<HttpData> holder_;
//	void setReadHandler(CallBack &&readHandler)
//	{
//		readHandler_ = readHandler;
//	}
//	void setWriteHandler(CallBack &&writeHandler)
//	{
//		writeHandler_ = writeHandler;
//	}
//	void setErrorHandler(CallBack &&errorHandler)
//	{
//		errorHandler_ = errorHandler;
//	}
//	void setConnHandler(CallBack &&connHandler)
//	{
//		connHandler_ = connHandler;
//	}
//
//	void setRevents(__uint32_t ev)
//	{
//		revents_ = ev;
//	}
//	void setEvents(__uint32_t ev)
//	{
//		events_ = ev;
//	}
//	__uint32_t& getEvents()
//	{
//		return events_;
//	}
//	bool EqualAndUpdateLastEvents()
//	{
//		bool ret = (lastEvents_ == events_);
//		lastEvents_ = events_;
//		return ret;
//	}
//	__uint32_t getLastEvents()
//	{
//		return lastEvents_;
//	}
//	int getFd();
//	void setFd(int fd);
//	void handleEvents()
//	{
//		events_ = 0;
//		if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
//		{
//			events_ = 0;
//			return;
//		}
//		if (revents_ & EPOLLERR)
//		{
//			if (errorHandler_) errorHandler_();
//			events_ = 0;
//			return;
//		}
//		if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
//		{
//			handleRead();
//		}
//		if (revents_ & EPOLLOUT)
//		{
//			handleWrite();
//		}
//		handleConn();
//	}
//	void handleRead();
//	void handleWrite();
//	void handleConn();
//};
//Channel::Channel(EventLoop *loop, int fd)
//	:
//	fd_(fd),
//	loop_(loop),
//	events_(0),
//	lastEvents_(0)
//{}
//int Channel::getFd() {
//	return fd_;
//}
//void Channel::setFd(int fd) {
//	fd_ = fd;
//}
//void Channel::handleRead() {
//	if (readHandler_) {
//		readHandler_();
//	}
//}
//
//void Channel::handleWrite()
//{
//	if (writeHandler_)
//	{
//		writeHandler_();
//	}
//}
//
//void Channel::handleConn()
//{
//	if (connHandler_)
//	{
//		connHandler_();
//	}
//}
//
//struct ThreadData {
//	typedef Thread::ThreadFunc ThreadFunc;
//	ThreadFunc func_;
//	string name_;
//	pid_t *tid_;
//	CountDownLatch *latch_;
//	ThreadData(const ThreadFunc &func, const string& name, pid_t *tid, CountDownLatch *latch)
//		:func_(func),
//		name_(name),
//		tid_(tid),
//		latch_(latch)
//	{}
//	void runInThread() {
//		*tid_ = CurrentThread::tid();
//		tid_ = NULL;
//		latch_->countDown();
//		latch_ = NULL;
//		CurrentThread::t_threadName = name_.empty() ? "Thread" : name_.c_str();
//		prctl(PR_SET_NAME, CurrentThread::t_threadName);
//		func_();
//		CurrentThread::t_threadName = "finished";
//	}
//};
//
//class Thread {
//public:
//	typedef function<void()> ThreadFunc;
//	Thread(const ThreadFunc&, const string& name = string());
//	~Thread();
//	void setDefaultName();
//	bool started() const { return started_; }
//	int join();
//	void start();
//	bool started_;
//	pid_t tid_;
//	CountDownLatch latch_;
//	bool joined_;
//	string name_;
//	ThreadFunc func_;
//	pthread_t pthreadId_;
//};
//Thread::Thread(const ThreadFunc& func, const string& n)
//	:started_(false),
//	joined_(false),
//	func_(func),
//	tid_(0),
//	latch_(1),
//	name_(n),
//	pthreadId_(0)
//{
//	setDefaultName();
//}
//Thread::~Thread() {
//	if (started_ && !joined_) {
//		pthread_detach(pthreadId_);
//	}
//}
//void Thread::setDefaultName()
//{
//	if (name_.empty())
//	{
//		char buf[32];
//		snprintf(buf, sizeof buf, "Thread");
//		name_ = buf;
//	}
//}
//void *startThread(void* obj) {
//	ThreadData* data = static_cast<ThreadData*>(obj);
//	data->runInThread();
//	delete data;
//	return NULL;
//}
//
//void Thread::start() {
//	assert(!started_);
//	started_ = true;
//	ThreadData* data = new ThreadData(func_, name_, &tid_, &latch_);
//	if (pthread_create(&pthreadId_, NULL, &startThread, data)) {
//		started_ = false;
//		delete data;
//	}
//	else {
//		latch_.wait();
//		assert(tid_ > 0);
//	}
//}
//int Thread::join() {
//	assert(started_);
//	assert(!joined_);
//	joined_ = true;
//	return pthread_join(pthreadId_, NULL);
//}
//
//class EventLoopThread {
//public:
//	EventLoopThread();
//	~EventLoopThread();
//	void threadFunc();
//	EventLoop* startLoop();
//	EventLoop *loop_;
//	Thread thread_;
//	Condition cond_;
//	MutexLock mutex_;
//	bool exiting_;
//};
//EventLoopThread::EventLoopThread() :
//	exiting_(false),
//	loop_(NULL),
//	thread_(bind(&EventLoopThread::threadFunc, this), "EventLoopThread"),
//	mutex_(),
//	cond_(mutex_)
//{
//}
//EventLoopThread::~EventLoopThread()
//{
//	exiting_ = true;
//	if (loop_ != NULL)
//	{
//		loop_->quit();
//		thread_.join();
//	}
//}
//void EventLoopThread::threadFunc() {
//	EventLoop loop;
//	{
//		MutexLockGuard lock(mutex_);
//		loop_ = &loop;
//		cond_.notify();
//	}
//	loop.loop();
//	loop_ = NULL;
//}
//EventLoop* EventLoopThread::startLoop() {
//	assert(!thread_.started());
//	thread_.start();
//	{
//		MutexLockGuard lock(mutex_);
//		while (loop_ == NULL) cond_.wait();
//	}
//	return loop_;
//}
//
//class EventLoopThreadPool {
//public:
//	EventLoopThreadPool(EventLoop* baseLoop, int numThreads);
//	EventLoop *baseLoop_;
//	int numThreads_;
//	void start();
//	bool started;
//	vector<std::shared_ptr< EventLoopThread> > threads_;
//	vector< EventLoop*> loops_;
//};
//EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, int numThreads)
//	:baseLoop_(baseLoop),
//	numThreads_(numThreads),
//	started(false)
//{
//	if (numThreads_ <= 0)
//	{
//		abort();
//	}
//}
//void EventLoopThreadPool::start() {
//	baseLoop_->assertInLoopThread();
//	started = true;
//	for (int i = 0; i < numThreads_; i++) {
//		std::shared_ptr< EventLoopThread> t(new EventLoopThread());
//		threads_.push_back(t);
//		loops_.push_back(t->startLoop());
//	}
//}
//
//class Server {
//public:
//	Server(EventLoop *loop, int threadNum, int port);
//	~Server() { }
//	EventLoop *loop_;
//	int threadNum_;
//	std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;
//	std::shared_ptr<Channel> acceptChannel_;
//	int port_;
//	int listenFd_;
//	void start();
//};
//Server::Server(EventLoop *loop, int threadNum, int port)
//	:loop_(loop),
//	threadNum_(threadNum),
//	eventLoopThreadPool_(new EventLoopThreadPool(loop_, threadNum)),
//	acceptChannel_(new Channel(loop_)),
//	port_(port),
//	listenFd_(socket_bind_listen(port_))
//{
//	acceptChannel_->setFd(listenFd_);
//	handle_for_sigpipe();
//	if (setSocketNonBlocking(listenFd_) < 0)
//	{
//		abort();
//	}
//}
//void Server::start() {
//	eventLoopThreadPool_->start();
//	acceptChannel_->setEvents(EPOLLIN | EPOLLET);
//	acceptChannel_->setReadHandler(bind(&Server::handNewConn, this));
//	acceptChannel_->setConnHandler(bind(&Server::handThisConn, this));
//}
//void Server::handNewConn()
//{
//	struct sockaddr_in client_addr;
//	memset(&client_addr, 0, sizeof(struct sockaddr_in));
//	socklen_t client_addr_len = sizeof(client_addr);
//	int accept_fd = 0;
//	while ((accept_fd = accept(listenFd_, (struct sockaddr*)&client_addr, &client_addr_len)) > 0)
//	{
//		EventLoop *loop = eventLoopThreadPool_->getNextLoop();
//		LOG << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port);
//		// cout << "new connection" << endl;
//		// cout << inet_ntoa(client_addr.sin_addr) << endl;
//		// cout << ntohs(client_addr.sin_port) << endl;
//		/*
//		// TCP的保活机制默认是关闭的
//		int optval = 0;
//		socklen_t len_optval = 4;
//		getsockopt(accept_fd, SOL_SOCKET,  SO_KEEPALIVE, &optval, &len_optval);
//		cout << "optval ==" << optval << endl;
//		*/
//		// 限制服务器的最大并发连接数
//		if (accept_fd >= MAXFDS)
//		{
//			close(accept_fd);
//			continue;
//		}
//		// 设为非阻塞模式
//		if (setSocketNonBlocking(accept_fd) < 0)
//		{
//			LOG << "Set non block failed!";
//			//perror("Set non block failed!");
//			return;
//		}
//
//		setSocketNodelay(accept_fd);
//		//setSocketNoLinger(accept_fd);
//
//		shared_ptr<HttpData> req_info(new HttpData(loop, accept_fd));
//		req_info->getChannel()->setHolder(req_info);
//		loop->queueInLoop(std::bind(&HttpData::newEvent, req_info));
//		//如果一直没有事情，poll不会返回。但是这时候有事情做，必须让poll返回，因此需要出点事情给poll，也就是wakup()。
////	这就是queueInLoop的原理
//	}
//	acceptChannel_->setEvents(EPOLLIN | EPOLLET);
//}
//int main2() {
//	int threadNum = 4;
//	int port = 80;
//	EventLoop mainloop;
//	Server myHTTPServer(&mainloop, threadNum, port);
//	myHTTPServer.start();
//
//	return 0;
//}