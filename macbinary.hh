#include <cstdlib>

template <class itype = const unsigned char *> class MacBinary {
    public:
        class ResourceFork;

        typedef itype iterator_type;

    private:
        const itype _begin, _end;
        /* XXX this should be an autoptr (or whatever modern equiv) */
        ResourceFork *_res = NULL;

    public:
        MacBinary(itype begin, itype end)
        : _begin(begin), _end(end)
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

template <class itype> class MacBinary<itype>::ResourceFork {
    friend class MacBinary<itype>;
    protected:
        ResourceFork() {}
};

template <class itype> typename MacBinary<itype>::ResourceFork &MacBinary<itype>::getResourceFork() {
    if (!_res) _res = new ResourceFork();
    return *_res;
}
