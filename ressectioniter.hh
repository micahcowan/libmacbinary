#ifndef RESSECTIONITER_HH
#define RESSECTIONITER_HH

#include <iterator>

#include "macbinary.hh"
#include "ressection.hh"

namespace libmacbinary {

class ResSectionIter :
    std::iterator<std::forward_iterator_tag, ResSection>

{
    friend class MacBinary::ResourceFork;

    private:
        MacBinary::ResourceFork *_rf;
        const unsigned char *_cur = NULL;
    protected:
        ResSectionIter(MacBinary::ResourceFork *rf);
    public:
        ResSectionIter()
            : _rf((MacBinary::ResourceFork *)(NULL))
            { }
        ~ResSectionIter();

        bool operator==(ResSectionIter &other)
        {
            return
                   (_rf == other._rf)
                && (_rf == NULL || _cur == other._cur);
        }
};

}

#endif // RESSECTIONITER_HH
