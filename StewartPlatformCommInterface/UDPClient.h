#pragma once
#include <SDKDDKVer.h>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

class UDPClient {
public:
	UDPClient(const std::string& ipAddress, const std::string& port);
	~UDPClient();

	void PrintSendBuffer(unsigned char*, int size);
	void Send(unsigned char* buff, int size);

private:
	boost::asio::io_service ioService;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint remoteEndpoint;
};