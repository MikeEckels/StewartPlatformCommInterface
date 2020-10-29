#include "UDPClient.h"

UDPClient::UDPClient(const std::string& ipAddress, const std::string& port) : socket{ ioService } {
    socket.open(boost::asio::ip::udp::v4());

    boost::asio::socket_base::broadcast option(true);
    socket.set_option(option);

    this->remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ipAddress), boost::lexical_cast<int>(port));
}

UDPClient::~UDPClient() {
	socket.close();
}

void UDPClient::Send(unsigned char* buff, int size) {
	const std::string stringBuffer(reinterpret_cast<const char*>(buff), size);
	socket.send_to(boost::asio::buffer(stringBuffer, size), this->remoteEndpoint, 0, this->ignoredError);
}
