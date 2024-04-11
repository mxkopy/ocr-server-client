#ifndef TCP_CLIENT
#define TCP_CLIENT

#include "dependencies.hpp"
#include "tcp_stream.hpp"

template <typename derived>
struct tcp_client {

    boost::asio::io_context& io_context;
    ip::tcp::acceptor& acceptor;
    derived* self;

    tcp_client(boost::asio::io_context& io_context, ip::tcp::acceptor& acceptor, derived* self):
        io_context(io_context),
        acceptor(acceptor),
        self(self)
    {}

    // tail-call optimized on -O2 so no stack overflow as far as i've tested
    void connect_handler(tcp_stream::pointer& stream)
    {
        self -> handle_connect(stream);
        connect_handler(stream);
    }

    void connect(ip::tcp::endpoint endpoint)
    {
        tcp_stream::pointer stream = tcp_stream::create(io_context);
        stream -> connect(endpoint);
        connect_handler(stream);
    }
};

#endif
