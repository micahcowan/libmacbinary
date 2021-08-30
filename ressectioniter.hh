#ifndef LIBMB_RESSECTIONITER_HH
#define LIBMB_RESSECTIONITER_HH

#include <iterator>
#include <string>

#include "ressection.hh"
#include "offsets.hh"

namespace libmacbinary {

class ResForkReader;

class ResSectionIter :
    std::iterator<std::forward_iterator_tag, ResSection>

{
    friend class ResForkReader;

    private:
        ResForkReader *_rf;
        const unsigned char *_cur = NULL;
    protected:
        ResSectionIter(ResForkReader *rf, const unsigned char *start)
            : _rf(rf), _cur(start)
            { }
    public:
        ResSectionIter()
            : _rf((ResForkReader *)(NULL))
            { }
        ~ResSectionIter() { }

        bool operator==(ResSectionIter &other)
        {
            return
                   (_rf == other._rf)
                && (_cur == other._cur);
        }

        bool operator!=(ResSectionIter &other)
        {
            return !(*this == other);
        }

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

#endif // LIBMB_RESSECTIONITER_HH
