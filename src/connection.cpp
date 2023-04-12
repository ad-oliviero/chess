#include "headers/connection.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket(const std::string& ip, const int port, bool type) : type(type) {
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
		if (bind(sock, reinterpret_cast<sockaddr*>(&extAddr), sizeof(extAddr)) == -1)
			throw std::runtime_error("Failed to bind socket to address and port");
		if (listen(sock, 1) == -1)
			throw std::runtime_error("Failed to start listening for incoming connections");
	} else if (type == Socket::Client) {
		extSock = sock;
		if (connect(sock, (struct sockaddr*)&extAddr, sizeof(extAddr)) < 0)
			throw std::runtime_error("Connection failed");
	}
}

Socket::~Socket() {
	close(sock);
	close(extSock);
}

void Socket::send(const std::string& msg) {
	if (::send(extSock, msg.c_str(), msg.size(), 0) < 0)
		throw std::runtime_error("Send failed");
}

std::string Socket::receive() {
	char buffer[1024] = {0};
	int valread;
	if ((valread = read(extSock, buffer, sizeof(buffer))) < 0)
		throw std::runtime_error("Read failed");
	return std::string(buffer, valread);
}

void Socket::run() {
	socklen_t addrlen = sizeof(extAddr);
	while (true) {
		extSock = accept(sock, reinterpret_cast<sockaddr*>(&extAddr), &addrlen);
		if (extSock == -1)
			std::cerr << "Failed to accept incoming connection" << std::endl;
		std::cout << "Client: " << receive() << std::endl;
		send("Yes, it does!");
		close(extSock);
	}
}
