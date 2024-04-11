#if defined(SERVER_MAIN)
#ifndef SERVER_SOURCE
#define SERVER_SOURCE

#include "tesseract_server.hpp"

int main(int argc, char* argv[])
{
    // setLeptDebugOK(1);
    std::vector<std::string> arguments(argv, argv + argc);

    boost::asio::io_context io_context;
    auto executor = io_context.get_executor();
    
    ip::tcp::resolver resolver(executor);
    ip::tcp::resolver::results_type endpoints;
    ip::tcp::endpoint endpoint;

    if(argc == 1)
    {
        arguments.push_back("127.0.0.1");
        arguments.push_back("1234");
    } 
    else if (argc == 2) 
        arguments.push_back(std::string("1234"));

    endpoints = resolver.resolve(arguments[1], arguments[2]);
    endpoint  = *endpoints.begin();

    ip::tcp::acceptor acceptor(io_context, endpoint);
    std::cout << "Tesseract Server Running..." << std::endl;
    tesseract_server server = tesseract_server(io_context, acceptor, NULL, "eng");
    io_context.run();
    return 0;
}

#endif
#endif