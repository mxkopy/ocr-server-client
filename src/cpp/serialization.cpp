#include "serialization.hpp"

void boost::serialization::serialize(boost::archive::binary_oarchive& ar, Pix& img, const unsigned int version)
{
    ar & img.w & img.h & img.d & img.spp & img.wpl & img.refcount & img.xres & img.yres & img.informat & img.special;
    ar & (img.text ? std::vector<char>(img.text, img.text + strlen(img.text)) : std::vector<char>{});
    ar & img.colormap;
    ar & boost::serialization::make_array(img.data, img.data ? img.w * img.h : 0);
}

void boost::serialization::serialize(boost::archive::binary_iarchive& ar, Pix& img, const unsigned int version)
{
    ar & img.w & img.h & img.d & img.spp & img.wpl & img.refcount & img.xres & img.yres & img.informat & img.special;
    img.data     = (l_uint32*)    malloc(img.h * img.w * sizeof(l_uint32));
    img.colormap = (PixColormap*) malloc(sizeof(PixColormap));
    std::vector<char> text = {};
    ar & text;
    ar & img.colormap;
    ar & boost::serialization::make_array(img.data, img.w * img.h);
    img.text = (text.empty() ? NULL : (char*) malloc(text.size() * sizeof(char)));
    std::copy(text.begin(), text.end(), img.text);
}

template<typename Archive>
void boost::serialization::serialize(Archive& ar, PixColormap& colormap, const unsigned int version)
{
    ar & boost::serialization::make_array((RGBA_Quad*) colormap.array, colormap.array ? colormap.nalloc : 0);
    ar & colormap.depth;
    ar & colormap.nalloc;
    ar & colormap.n;
};

template<typename Archive>
void boost::serialization::serialize(Archive& ar, RGBA_Quad& q, const unsigned int version)
{
    ar & q.blue;
    ar & q.green;
    ar & q.red;
    ar & q.alpha;
};