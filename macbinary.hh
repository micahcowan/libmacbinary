#ifndef MACBINARY_HH
#define MACBINARY_HH

#include <cstdlib>
#include <cstdint>

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

class MacBinary::ResourceFork {
    friend class MacBinary;
    private:
        MacBinary                 & _mb;
        const unsigned char * const _data;
        const std::size_t           _len;
    protected:
        ResourceFork(MacBinary &mb, const unsigned char *p, std::size_t len)
            : _mb(mb), _data(p), _len(len)
            {}
    public:
        virtual ~ResourceFork() {}


};

#endif // MACBINARY_HH
