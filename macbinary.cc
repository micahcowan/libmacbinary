#include "macbinary.hh"

using std::uint16_t;
using std::size_t;

MacBinary::ResourceFork & MacBinary::getResourceFork()
{
    const unsigned char *resStart;
    std::size_t resLen;

    // XXX confirm we don't run past _len
    resStart = _data + 128u + _getU16(83u);
    resLen   = _getU16(87u);
    // XXX ensure multiples of 128

    if (!_res) _res = new ResourceFork(*this, resStart, resLen);
    return *_res;
}

