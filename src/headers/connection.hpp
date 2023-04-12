#ifndef _CONNECTION_HPP_
#define _CONNECTION_HPP_
#include <netinet/in.h>
#include <string>

class Socket {
public:
	Socket(const std::string&, const int, bool);
	~Socket();
	void send(const std::string&);
	std::string receive();
	void run();

	enum connType { Client = false,
									Server = true };

private:
	bool type;
	int sock;
	int extSock;
	sockaddr_in extAddr;
};

#endif // _CONNECTION_HPP_