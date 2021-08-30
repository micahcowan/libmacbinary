#ifndef LIBMB_RESTYPELISTIONITER_HH
#define LIBMB_RESTYPELISTITER_HH

#include <iterator>
#include <string>

#include "restypeentry.hh"
#include "offsets.hh"

namespace libmacbinary {

class ResForkReader;

class ResTypeListIterator :
    std::iterator<std::forward_iterator_tag, ResTypeEntry>

{
    friend class ResForkReader;

    private:
        ResForkReader *_rf;
        const unsigned char *_cur = NULL;
    protected:
        ResTypeListIterator(ResForkReader *rf, const unsigned char *start)
            : _rf(rf), _cur(start)
            { }
    public:
        ResTypeListIterator()
            : _rf((ResForkReader *)(NULL))
            { }
        ~ResTypeListIterator() { }

        bool operator==(ResTypeListIterator &other)
        {
            return
                   (_rf == other._rf)
                && (_cur == other._cur);
        }

        bool operator!=(ResTypeListIterator &other)
        {
            return !(*this == other);
        }

        ResTypeListIterator operator++()
        {
            _cur += RFTLE_SIZE;
            return *this;
        }

        const ResTypeEntry operator*() {
            return ResTypeEntry(this, _cur);
        }
};

}

#endif // LIBMB_RESTYPELISTITER_HH
