#ifndef _CONNECTION_HPP_
#define _CONNECTION_HPP_
#include <netinet/in.h>
#include <string>
#include <thread>

template <typename T>
class Socket {
public:
	int sock;
	int extSock;
	sockaddr_in extAddr;
	socklen_t addrLen;

	Socket(const std::string&, const int, bool);
	~Socket();
	void send(const T&);
	const T receive();
	void setLoop(void (*)(Socket<T>&));
	void startLoop();
	void stopLoop();
	void loop();
	void closeExt();
	void closeSock();
	void close();
	void accept();

	bool isRunning() const { return running; }

	enum connType { Client = false,
									Server = true };

private:
	bool type;
	bool running;
	void (*loopCallbackPtr)(Socket<T>&);
	std::thread* thread;
};

#endif // _CONNECTION_HPP_
