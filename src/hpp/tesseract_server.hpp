#ifndef SERVER
#define SERVER

#include "dependencies.hpp"
#include "tcp_server.hpp"

struct tesseract_server : tesseract::TessBaseAPI, tcp_server<tesseract_server> {

    tesseract_server(boost::asio::io_context& io_context, ip::tcp::acceptor& acceptor, char* datapath, const char* languages) : 
        tesseract::TessBaseAPI(),
        tcp_server(io_context, acceptor, this)
    {
        Init(datapath, languages);
    };

    ~tesseract_server()
    {
        End();
    }

    void handle_accept(tcp_stream::pointer connection)
    {
        Pix* img = connection -> recv<Pix*>();
        SetImage(img);
        char* result = GetUTF8Text();
        std::string str(result);
        connection -> send(str);
        delete [] result;
    }
};

#endif
