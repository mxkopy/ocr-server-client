#ifndef CLIENT
#define CLIENT

#include "dependencies.hpp"
#include "tcp_client.hpp"

struct tesseract_client : tcp_client<tesseract_client> {

    tesseract_client(boost::asio::io_context& io_context, ip::tcp::acceptor& acceptor) : 
        tcp_client(io_context, acceptor, this)
    {};

    void handle_connect(tcp_stream::pointer connection)
    {
        Pix* img = pixRead("image.png");
        connection -> send(img);
        std::string out = connection -> recv<std::string>();
        std::cout << out << std::endl;
    }

};
#endif