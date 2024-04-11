#ifndef TCP_STREAM
#define TCP_STREAM

#include "dependencies.hpp"
#include "serialization.hpp"

using namespace boost::asio;

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

    static pointer create(boost::asio::io_context& io_context, ip::tcp::endpoint endpoint)
    {
        return pointer(new tcp_stream(io_context, endpoint));
    }

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_stream(io_context));
    }

    auto& socket(){
        return stream.socket();
    }

    template<typename T>
    void recv(T& data)
    {
        iarchive >> data;
    }

    template<typename T>
    T recv()
    {
        T data;
        iarchive >> data;
        return data;
    }

    template<typename T>
    void send(T object)
    {   
        oarchive << object;
        stream.flush();
    }

    void connect(ip::tcp::endpoint endpoint){
        stream.connect(endpoint);
    }

    void close()
    {
        stream.close();
    }

};

#endif