#ifndef TCP_SERVER
#define TCP_SERVER

#include "dependencies.hpp"
#include "tcp_stream.hpp"

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
