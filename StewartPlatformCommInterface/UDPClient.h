#pragma once
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

class UDPClient {
public:
	//UDPClient(boost::asio::io_service& service, const std::string& ipAddress, short port);
	UDPClient(boost::asio::io_service& service, const std::string& ipAddress, const std::string& port);
	~UDPClient();

	void Send(unsigned char* buff, int size);

private:
	boost::asio::io_service& ioService;
	boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint remoteEndpoint;
	boost::system::error_code ignoredError;
};