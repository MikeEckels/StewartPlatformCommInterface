#include "UDPClient.h"

//UDPClient::UDPClient(boost::asio::io_service& service, const std::string& ipAddress, short port) : socket{ service } {
//	boost::asio::ip::udp::endpoint remoteEndpoint;
//	boost::asio::socket_base::broadcast option(true);
//
//	socket.open(boost::asio::ip::udp::v4());
//	socket.set_option(option);
//
//	remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::make_address(ipAddress), boost::lexical_cast<int>(port));
//}

UDPClient::UDPClient(const std::string& ipAddress, short port) : socket{ ioService } {
    //boost::asio::ip::udp::udp::resolver resolver(io_service_);
    //boost::asio::ip::udp::udp::resolver::query query(boost::asio::ip::udp::udp::v4(), host, port);
    //boost::asio::ip::udp::udp::resolver::iterator iter = resolver.resolve(query);
    //endpoint_ = *iter;
    boost::asio::socket_base::broadcast option(true);

    socket.open(boost::asio::ip::udp::v4());
    socket.set_option(option);

    this->remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::make_address(ipAddress), boost::lexical_cast<int>(port));
}

UDPClient::~UDPClient() {
	socket.close();
}

void UDPClient::Send(unsigned char* buff, int size) {
	const std::string stringBuffer(reinterpret_cast<const char*>(buff), size);
	socket.send_to(boost::asio::buffer(stringBuffer, size), this->remoteEndpoint, 0, this->ignoredError);
}
