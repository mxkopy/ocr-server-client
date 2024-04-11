#ifndef SERIALIZATION
#define SERIALIZATION

#include "dependencies.hpp"

namespace boost::serialization {

// Sending
void serialize(boost::archive::binary_oarchive& ar, Pix& img, const unsigned int version);
// Receiving
void serialize(boost::archive::binary_iarchive& ar, Pix& img, const unsigned int version);

template<typename Archive>
void serialize(Archive& ar, PixColormap& colormap, const unsigned int version);

template<typename Archive>
void serialize(Archive& ar, RGBA_Quad& q, const unsigned int version);

}
#endif