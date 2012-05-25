#include <string>
#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Usage: spider-cpp <URL>" << std::endl;
        return 1;
    }

    using boost::asio::ip::tcp;

    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);

    std::string url = argv[1];
    tcp::resolver::query query(url, "http");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    const std::string newline = "\r\n";
    request_stream << "GET / HTTP/1.0" << newline;
    request_stream << "Host: " << url << newline;
    request_stream << newline;

    boost::asio::write(socket, request);
    
    boost::asio::streambuf response;
    boost::system::error_code error;
    while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {
        std::cout << &response;
    }
    if (error != boost::asio::error::eof) {
        std::cout << boost::system::system_error(error).what() << std::endl;
    }
    
    return 0;
}
