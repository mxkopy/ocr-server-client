#ifndef TCP_STREAM
#define TCP_STREAM

#include "dependencies.hpp"
#include "serialization.hpp"

using namespace boost::asio;

/*
This class allows the use of Boost archives for serialization over Boost TCP sockets
(more specifically, TCP iostreams, since archives work on iostreams).
Some basic functions matching the socket interface are implemented. 
*/

struct tcp_stream : public std::enable_shared_from_this<tcp_stream> {

    boost::asio::io_context& io_context;
    ip::tcp::iostream stream;
    boost::archive::binary_iarchive iarchive;
    boost::archive::binary_oarchive oarchive;

    boost::system::error_code error;

    typedef std::shared_ptr<tcp_stream> pointer;

    tcp_stream(boost::asio::io_context& io_context) :
        io_context(io_context),
        stream(ip::tcp::socket(io_context)),
        iarchive(stream, boost::archive::no_header),
        oarchive(stream, boost::archive::no_header)
    {};

    tcp_stream(boost::asio::io_context& io_context, ip::tcp::endpoint endpoint):
        tcp_stream(io_context)
    {
        connect(endpoint);
    }

    // Creates a new tcp_stream and returns it in a shared_ptr. 
    static pointer create(boost::asio::io_context& io_context, ip::tcp::endpoint endpoint)
    {
        return pointer(new tcp_stream(io_context, endpoint));
    }

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_stream(io_context));
    }

    // Returns the iostream's underlying socket.
    auto& socket(){
        return stream.socket();
    }

    // This is blocking
    template<typename T>
    void recv(T& data)
    {
        iarchive >> data;
    }

    // This is blocking
    template<typename T>
    T recv()
    {
        T data;
        iarchive >> data;
        return data;
    }

    // This is blocking
    template<typename T>
    void send(T object)
    {   
        oarchive << object;
        stream.flush();
    }

    void connect(ip::tcp::endpoint endpoint)
    {
        stream.connect(endpoint);
    }

    void close()
    {
        stream.close();
    }

};

#endif