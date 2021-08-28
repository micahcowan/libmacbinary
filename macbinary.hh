#ifndef MACBINARY_HH
#define MACBINARY_HH

#include <cstdlib>

class MacBinary {
    public:
        class ResourceFork {
            friend class MacBinary;
            protected:
                ResourceFork() {}
        };

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
        XXX
        This should return an iterator over unsigned char, that is equal to
        an "end" iterator when it reaches the end of the data fork, and throws
        exceptions if dereferenced past there (or before the start).
        
        public const unsigned char *getDataFork();
        */
        virtual ResourceFork &getResourceFork();

        virtual ~MacBinary() {}
};

#endif // MACBINARY_HH
