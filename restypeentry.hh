#ifndef LIBMB_RESTYPEENTRY_HH
#define LIBMB_RESTYPEENTRY_HH

#include <string>
#include <ostream>

namespace libmacbinary {

class ResTypeListIterator;

class ResTypeEntry
{
    friend class ResTypeListIterator;

    private:
        ResTypeListIterator *_iter;
        const unsigned char *_entry;
        const std::string _tid;

    protected:
        ResTypeEntry(ResTypeListIterator *iter, const unsigned char *p)
            : _iter(iter), _entry(p), _tid((const char *)p, 4)
        {
        }

    public:
        const std::string &typeId () const { return _tid; }
};

std::ostream &operator<<(std::ostream &out, const ResTypeEntry &re)
{
    return out << re.typeId();
}

}

#endif // LIBMB_RESTYPEENTRY_HH
