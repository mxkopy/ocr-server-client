#ifndef TESSERACT_CLIENT
#define TESSERACT_CLIENT

#include "dependencies.hpp"

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
        Pix* img = pixRead("test/test.png");
        connection -> send(img);
        std::string out = connection -> recv<std::string>();
        std::cout << out << std::endl;
    }
    
};
#endif