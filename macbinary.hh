#ifndef MACBINARY_HH
#define MACBINARY_HH

#include <cstdlib>
#include <cstdint>

namespace libmacbinary {

class MacBinary {
    public:
        class ResourceFork;

    private:
        const unsigned char * const _data;
        const std::size_t _len;
        /* XXX this should be an autoptr (or whatever modern equiv) */
        ResourceFork *_res = NULL;

    protected:
        std::uint16_t _getU16(std::size_t loc) {
            return _data[loc] * 256 + _data[loc + 1];
        }

    public:
        MacBinary(const unsigned char *p, std::size_t len)
        : _data(p), _len(len)
        { }

        /*
        XXX
        This should return an iterator over unsigned char, that is equal to
        an "end" iterator when it reaches the end of the data fork, and throws
        exceptions if dereferenced past there (or before the start).
        
        public const unsigned char *getDataFork();
        */
        virtual ResourceFork &getResourceFork();

        virtual ~MacBinary() {}
};

class ResSectionIter;

class MacBinary::ResourceFork {
    friend class MacBinary;
    private:
        MacBinary                  *_mb;
        const unsigned char * const _data;
        const std::size_t           _len;
    protected:
        ResourceFork(MacBinary *mb, const unsigned char *p, std::size_t len)
            : _mb(mb), _data(p), _len(len)
            {}
        std::uint16_t _getU16(std::size_t loc)
        {
            return _data[loc] * 256 + _data[loc + 1];
        }
        std::uint32_t _getU32(std::size_t loc)
        {
            const unsigned char *u = _data + loc;
            const unsigned char *ue = u + 4;
            std::uint32_t val = 0;
            for (; u != ue; ++u) {
                val <<= 8;
                val += *u;
            }
            return val;
        }

        const unsigned char *_mapStart_p();
        const unsigned char *_tlStart_p();
    public:
        virtual ~ResourceFork() {}

        ResSectionIter getSections();
        ResSectionIter getSectionsEnd();

        // Debug utils, public
        std::size_t _start() { return _data - _mb->_data; }
        std::size_t _mapStart() { return _mapStart_p() - _mb->_data; }
        std::size_t _tlStart()  { return _tlStart_p()  - _mb->_data; }
        std::size_t _numTypes();
};

}

#endif // MACBINARY_HH
