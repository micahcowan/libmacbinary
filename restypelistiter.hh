#ifndef LIBMB_RESTYPELISTITER_HH
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
        const ResForkReader *_rf;
        const unsigned char *_cur = NULL;
    protected:
        ResTypeListIterator(const ResForkReader *rf, const unsigned char *start)
            : _rf(rf), _cur(start)
            { }
    public:
        ResTypeListIterator()
            : _rf((const ResForkReader *)(NULL))
            { }
        ~ResTypeListIterator() { }

        bool operator== (const ResTypeListIterator &other) const
        {
            return
                   (_rf == other._rf)
                && (_cur == other._cur);
        }

        bool operator!= (const ResTypeListIterator &other) const
        {
            return !(*this == other);
        }

        ResTypeListIterator operator++()
        {
            _cur += RFTLE_SIZE;
            return *this;
        }

        const ResTypeEntry operator*() const {
            return ResTypeEntry(this, _cur);
        }
};

}

#endif // LIBMB_RESTYPELISTITER_HH
