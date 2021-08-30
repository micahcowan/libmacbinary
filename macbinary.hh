#ifndef LIBMB_MACBINARY_HH
#define LIBMB_MACBINARY_HH

#include <cstdlib>

#include "bigendian.hh"
#include "offsets.hh"

namespace libmacbinary {

class MacBinary {
    public:
        class ResourceFork;

    private:
        const unsigned char * const _data;
        const std::size_t _len;
        /* XXX this should be an autoptr (or whatever modern equiv) */
        ResourceFork *_res = NULL;

    public:
        MacBinary(const unsigned char *p, std::size_t len)
        : _data(p), _len(len)
        { }

        /*
        const unsigned char *getDataFork(const unsigned char **end);
        */
        const unsigned char *getResourceFork (const unsigned char **end) const
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
};

}

#endif // LIBMB_MACBINARY_HH
