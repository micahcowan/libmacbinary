#ifndef LIBMB_MACBINARY_HH
#define LIBMB_MACBINARY_HH

#include <cstdlib>

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
        const unsigned char *getResourceFork (const unsigned char **end) const;
};

}

#endif // LIBMB_MACBINARY_HH
