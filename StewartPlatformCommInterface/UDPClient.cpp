#include "UDPClient.h"

UDPClient::UDPClient(boost::asio::io_service& service, std::string ipAddress, short port) : socket{ service } {
	boost::asio::ip::udp::endpoint remoteEndpoint;
	boost::asio::socket_base::broadcast option(true);

	socket.open(boost::asio::ip::udp::v4());
	socket.set_option(option);

	remoteEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::make_address(ipAddress), boost::lexical_cast<int>(port));
}

UDPClient::~UDPClient() {
	socket.close();
}

void UDPClient::Send(unsigned char* buff, int size) {
	const std::string stringBuffer(reinterpret_cast<const char*>(buff), size);
	socket.send_to(boost::asio::buffer(stringBuffer, size), this->remoteEndpoint, 0, this->ignoredError);
}
