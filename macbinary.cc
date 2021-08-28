#include "macbinary.hh"
#include "ressectioniter.hh"
#include "offsets.hh"

using namespace libmacbinary;

using std::uint16_t;
using std::size_t;

MacBinary::ResourceFork & MacBinary::getResourceFork()
{
    const unsigned char *resStart;
    std::size_t resLen;

    // XXX confirm we don't run past _len
    resStart = _data + MB_HEADER_LENGTH + _getU16(MB_F_DATA_FORK_LENGTH);
    resLen   = _getU16(MB_F_RES_FORK_LENGTH);
    // XXX ensure multiples of 128

    if (!_res) _res = new ResourceFork(this, resStart, resLen);
    return *_res;
}

ResSectionIter MacBinary::ResourceFork::getSections() {
    return ResSectionIter(this);
}
