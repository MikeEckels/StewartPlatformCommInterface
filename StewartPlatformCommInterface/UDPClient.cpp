#include "UDPClient.h"

UDPClient::UDPClient(const std::string& ipAddress, const std::string& port) : socket{ ioService } {
    socket.open(boost::asio::ip::udp::v4());
    socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8410));

    socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket.set_option(boost::asio::socket_base::broadcast(true));

    //this->remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ipAddress), boost::lexical_cast<int>(port));
    this->remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::broadcast(), boost::lexical_cast<int>(port));
}

UDPClient::~UDPClient() {
	socket.close();
}

void UDPClient::Send(unsigned char* buff, int size) {
	const std::string stringBuffer(reinterpret_cast<const char*>(buff), size);
	socket.send_to(boost::asio::buffer(stringBuffer, size), this->remoteEndpoint);
}
