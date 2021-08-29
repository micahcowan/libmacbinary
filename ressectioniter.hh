#ifndef RESSECTIONITER_HH
#define RESSECTIONITER_HH

#include <iterator>
#include <string>

#include "macbinary.hh"
#include "ressection.hh"
#include "offsets.hh"

namespace libmacbinary {

class ResSectionIter :
    std::iterator<std::forward_iterator_tag, ResSection>

{
    friend class MacBinary::ResourceFork;

    private:
        MacBinary::ResourceFork *_rf;
        const unsigned char *_cur = NULL;
    protected:
        ResSectionIter(MacBinary::ResourceFork *rf, const unsigned char *start)
            : _rf(rf), _cur(start)
            { }
    public:
        ResSectionIter()
            : _rf((MacBinary::ResourceFork *)(NULL))
            { }
        ~ResSectionIter() { }

        bool operator==(ResSectionIter &other)
        {
            return
                   (_rf == other._rf)
                && (_cur == other._cur);
        }

#if 1
        bool operator!=(ResSectionIter &other)
        {
            return !(*this == other);
        }
#endif

        ResSectionIter operator++()
        {
            _cur += RFTLE_SIZE;
            return *this;
        }

        ResSection operator*() {

            return std::string((const char *)_cur, 4);
        }
};

}

#endif // RESSECTIONITER_HH
