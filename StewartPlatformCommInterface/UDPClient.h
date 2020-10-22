#pragma once
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iomanip>

class udp_client {
public:
    udp_client(boost::asio::io_service& io_service, const std::string& host, const std::string& port) : io_service_(io_service), socket_(io_service, boost::asio::ip::udp::udp::endpoint(boost::asio::ip::udp::udp::v4(), 0)) {
        boost::asio::ip::udp::udp::resolver resolver(io_service_);
        boost::asio::ip::udp::udp::resolver::query query(boost::asio::ip::udp::udp::v4(), host, port);
        boost::asio::ip::udp::udp::resolver::iterator iter = resolver.resolve(query);
        endpoint_ = *iter;
    }

    ~udp_client() {
        std::cout << "Calling UDP client destructor" << std::endl;
        socket_.close();
    }

    void send(unsigned char* buff) {
        //void send(const std::string& msg) {
            //socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_);

        const std::string stringBuff(reinterpret_cast<char const*>(buff));
        socket_.send_to(boost::asio::buffer(stringBuff, 50), endpoint_);
        std::cout << "Sending UDP data" << std::endl;
    }

    void recieve_from() {
        /*Initialize our endpoint*/
        boost::array<unsigned char, 7408> temp;
        size_t len = socket_.receive_from(boost::asio::buffer(temp), sender_endpoint);

        std::ostringstream ss;
        ss << std::hex << std::uppercase << std::setfill('0');
        std::for_each(temp.cbegin(), temp.cend(), [&](int c) { ss << std::setw(2) << c; });
        std::string result = ss.str();
        std::cout << "Length of recieved message " << len << std::endl;
        std::cout << result << std::endl;
    }

private:
    boost::asio::io_service& io_service_;
    boost::asio::ip::udp::udp::socket socket_;
    boost::asio::ip::udp::udp::endpoint endpoint_;
    //boost::array<char, 2048> recv_buf;
    std::vector<unsigned char> recv_buf;
    boost::asio::ip::udp::endpoint sender_endpoint;
};

inline void runUDPClient(std::string portStr, unsigned char* buffer)
{
    try
    {
        boost::asio::io_service io_service;
        udp_client client(io_service, "192.168.15.20", "8410");
        client.send(buffer);
        client.recieve_from();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

