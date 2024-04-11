# Optical Character Recognition Server
This code implements a simple asynchronous Tesseract-OCR server and synchronous client. When possible, functionality relies on external libraries, and few new dependencies are introduced (for example, Leptonica Pix objects, the native representation of image data underlying Tesseract, are serialized using Boost archives and sent over the network using Boost asio sockets).

Currently, this is only a proof of concept, but has some basic primitives implemented for a more fully-featured application. These include:
- a generic serialization wrapper around Boost TCP sockets (`tcp_stream.hpp`)
- a generic asynchronous TCP server class for streaming connections (`tcp_server.hpp`)
- a generic synchronous TCP client class for streaming connections (`tcp_client.hpp`)
- serialization methods for the Leptonica Pix struct (`serialization.hpp`)

# Testing 
You can install the dependencies with:
`sudo apt install tesseract-ocr libtesseract-dev libboost-all-dev libpng-dev`

Then, run
`make server client`
to build the server and client binaries, then 
`./server HOST SERVICE/PORT`
to run the server and 
`./client HOST SERVICE/PORT` 
to run the client. 

Host defaults to `127.0.0.1` and port defaults to `1234`. 

You can stop the server and client with CTRL-C. 

Right now all the client does is read `image.png` in the current directory, send it to the server, print the response, and loop. 