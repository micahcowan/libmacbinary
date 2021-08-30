#ifndef LIBMB_MACBINARY_HH
#define LIBMB_MACBINARY_HH

#include <iostream>

#include <cstdlib>
#include <cstdint>

#include "bigendian.hh"
#include "offsets.hh"

namespace libmacbinary {

inline std::uint16_t pad(std::uint16_t p, std::uint16_t orig)
{
    return (orig / p) * p + (orig % p == 0? 0 : p);
}

class MacBinary {
    public:
        class ResourceFork;

    private:
        const unsigned char * const _data;
        const std::size_t _len;

    public:
        MacBinary(const unsigned char *p, std::size_t len)
        : _data(p), _len(len)
        { }

        /*
        const unsigned char *getDataFork(const unsigned char **end);
        */
        const unsigned char *getResourceFork () const
        {
            const unsigned char *resStart;
            std::size_t resLen;

            return _data + MB_HEADER_LENGTH
                + pad(128, get_be_u32(&_data[MB_F_DATA_FORK_LENGTH]));
        }
        const unsigned char *getResourceForkEnd () const
        {
            std::size_t resLen, resLenPad, resFileEnd;

            using std::cerr;
            using std::endl;

            const unsigned char *resStart = getResourceFork();

            // how many bytes after the start of the resource fork does
            // the file end?
            resFileEnd = _len - (resStart - _data);

            resLen   = get_be_u32(&_data[MB_F_RES_FORK_LENGTH]);
            // ensure multiples of 128
            resLenPad = pad(128, resLen);

            if (resFileEnd == resLenPad) {
                // all is just as it should be
                resLen = resLenPad;
            }
            else if (resFileEnd > resLenPad) {
                cerr << "NOTE: Extra data after res fork ends." << endl;
                cerr << "  (" << (resFileEnd - resLenPad) << " bytes)" << endl;
                resLen = resLenPad;
            }
            else if (resFileEnd >= resLen) {
                cerr << "NOTE: file ends early, but still has space for full (unpadded) res fork." << endl;
            }
            else {
                cerr << "WARNING: file ends before res fork does!" << endl;
                resLen = resFileEnd;
            }

            return resStart + resLen;
        }
};

}

#endif // LIBMB_MACBINARY_HH
