#ifndef TCP_CLIENT
#define TCP_CLIENT

#include "dependencies.hpp"
#include "tcp_stream.hpp"

/*
This class implements a synchronous client interface.
Classes that inherit this server and set its template 
to their type (i.e. use the CRTP) need only implement 
the non-looping handle_connect(tcp_stream::pointer& stream) method. 
See tesseract_client.hpp for an example.
handle_connect is basically what the client should do to a connection
it establishes (i.e. it should contain the send/recv calls that 
define the protocol).
*/

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
