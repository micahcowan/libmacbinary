#include "macbinary.hh"
#include "offsets.hh"
#include "bigendian.hh"

using namespace libmacbinary;

using std::uint16_t;
using std::size_t;

const unsigned char * MacBinary::getResourceFork(const unsigned char **end) const
{
    const unsigned char *resStart;
    std::size_t resLen;

    // XXX confirm we don't run past _len
    // XXX MATH US WRONG: data should be padded to 128-byte boundary
    resStart = _data + MB_HEADER_LENGTH + get_be_u16(&_data[MB_F_DATA_FORK_LENGTH]);
    resLen   = get_be_u16(&_data[MB_F_RES_FORK_LENGTH]);
    // XXX ensure multiples of 128

    *end = resStart + resLen;
    return resStart;
}
