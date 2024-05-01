#include <iostream>
#include <boost/asio.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
#include <png.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <virtue_network/tcp_stream.hpp>
#include <virtue_network/tcp_client.hpp>
#include <virtue_network/tcp_server.hpp>
#include <virtue_network/serialization.hpp>

