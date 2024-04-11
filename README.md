# Optical Character Recognition Server
This code implements a simple asynchronous Tesseract-OCR server and synchronous client. When possible, functionality relies on external libraries, and few new dependencies are introduced (for example, Leptonica Pix objects, the native representation of image data underlying Tesseract, are serialized using Boost Archives and sent over the network using Boost Asio sockets).

Currently, this is only a proof of concept, but has some basic primitives implemented for a more fully-featured application. These include:
- a generic serialization wrapper around Boost TCP sockets
- a generic asynchronous TCP server base class for streaming connections
- a generic synchronous TCP client base class for streaming connections 
- serialization methods for the Leptonica Pix struct

# Testing 
Run
`make server client`
to build the server and client binaries, then 
`./server HOST SERVICE/PORT`
to run the server and 
`./client HOST SERVICE/PORT` 
to run the client. 

Host defaults to `127.0.0.1` and port defaults to `1234`. 


You can stop the server and client with CTRL-C. 

Right now all the client does is read `image.png` in the current directory, send it to the server, print the response, and loop. 