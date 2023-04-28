#include "headers/connection.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

template class Socket<std::string>;

template <typename T>
Socket<T>::Socket(const std::string& ip, const int port, bool type) : type(type), addrLen(sizeof(extAddr)), loopCallbackPtr(NULL), thread(NULL), running(false) {
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("Failed to create socket");
	if (type == Socket::Server) {
		int opt = 1;
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
			throw std::runtime_error("Failed to set socket options");
	}

	extAddr.sin_family = AF_INET;
	extAddr.sin_port	 = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &extAddr.sin_addr) <= 0)
		throw std::runtime_error("Invalid address/ Address not supported");
	if (type == Socket::Server) {
		if (bind(sock, reinterpret_cast<sockaddr*>(&extAddr), addrLen) == -1)
			throw std::runtime_error("Failed to bind socket to address and port");
		if (listen(sock, 1) == -1)
			throw std::runtime_error("Failed to start listening for incoming connections");
	} else if (type == Socket::Client) {
		extSock = sock;
		if (connect(sock, (struct sockaddr*)&extAddr, addrLen) < 0)
			throw std::runtime_error("Connection failed");
	}
}

template <typename T>
Socket<T>::~Socket() {
	close();
	stopLoop();
}

template <typename T>
void Socket<T>::closeExt() {
	::close(extSock);
}

template <typename T>
void Socket<T>::closeSock() {
	::close(sock);
}

template <typename T>
void Socket<T>::close() {
	closeExt();
	closeSock();
}

template <typename T>
void Socket<T>::accept() {
	extSock = ::accept(sock, reinterpret_cast<sockaddr*>(&extAddr), &addrLen);
}

template <typename T>
void Socket<T>::send(const T& msg) {
	if (::send(extSock, msg.c_str(), msg.size(), 0) < 0)
		throw std::runtime_error("Send failed");
}

template <typename T>
const T Socket<T>::receive() {
	char buffer[1024] = {0};
	int valread;
	if ((valread = read(extSock, buffer, sizeof(buffer))) < 0)
		throw std::runtime_error("Read failed");
	if (std::is_same<T, std::string>::value)
		return T(buffer, valread);
	return T(buffer);
}

template <typename T>
void Socket<T>::setLoop(void (*loopCallbackPtr)(Socket<T>&)) {
	this->loopCallbackPtr = loopCallbackPtr;
}

template <typename T>
void Socket<T>::startLoop() {
	running = true;
	thread	= new std::thread(&Socket<T>::loopCallback, this);
}

template <typename T>
void Socket<T>::stopLoop() {
	running = false;
	thread->join();
	delete thread;
	thread = NULL;
}

template <typename T>
void Socket<T>::loopCallback() {
	if (loopCallbackPtr)
		while (running)
			loopCallbackPtr(*this);
}
