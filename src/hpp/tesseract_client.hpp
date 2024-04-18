#ifndef CLIENT
#define CLIENT

#include "dependencies.hpp"
#include "tcp_client.hpp"

#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

struct tesseract_client : tcp_client<tesseract_client> {

    tesseract_client(boost::asio::io_context& io_context, ip::tcp::acceptor& acceptor) : 
        tcp_client(io_context, acceptor, this)
    {};

    void handle_connect(tcp_stream::pointer connection)
    {
        connection -> send(std::string("echo"));
        std::string test = connection -> recv<std::string>();
        std::cout << test << std::endl;
    }

};
#endif