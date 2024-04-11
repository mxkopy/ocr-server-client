#ifndef TCP_SERVER
#define TCP_SERVER

#include "dependencies.hpp"
#include "tcp_stream.hpp"

/*
This class implements an asynchronous server interface.
Classes that inherit this server and set its template 
to their type (i.e. use the CRTP) need only implement 
the non-looping handle_accept(tcp_stream::pointer& stream) method. 
See tesseract_server.hpp for an example.
handle_accept is basically what the server should do to a connection it receives
(i.e. it should contain the send/recv calls that define the protocol).
*/

template <typename derived>
struct tcp_server {

    boost::asio::io_context& io_context;
    ip::tcp::acceptor& acceptor;

    derived* self;

    tcp_server(boost::asio::io_context& io_context, ip::tcp::acceptor& acceptor, derived* self):
        io_context(io_context),
        acceptor(acceptor), 
        self(self)
    {
        async_accept();
    }

    void async_handle_accept(tcp_stream::pointer stream)
    {
        boost::asio::post(
            io_context, 
            [&, stream]()
            {
                try
                {
                    self -> handle_accept(stream);
                    async_handle_accept(stream);
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Connection closed with error:" << std::endl << e.what() << std::endl;
                }
            }
        );
    }

    void async_accept()
    {
        tcp_stream::pointer stream = tcp_stream::create(io_context);
        acceptor.async_accept(
            stream -> socket(),
            [&, stream](const boost::system::error_code& init_error)
            {
                if(!init_error)
                {
                    async_handle_accept(stream);
                    async_accept();
                }
                else 
                {
                    std::cerr << "Accepting new connection failed with error:" << std::endl << init_error.message() << std::endl;
                }
            }
        );
    }
};

#endif
