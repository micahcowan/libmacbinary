#ifndef LIBMB_RESTYPEENTRY_HH
#define LIBMB_RESTYPEENTRY_HH

#include <string>
#include <ostream>

#include <cstdlib>

#include "offsets.hh"
#include "bigendian.hh"

#include "restypelistiter.hh"
#include "resforkreader.hh"

namespace libmacbinary {

class ResTypeListIterator;

class ResTypeEntry
{
    friend class ResTypeListIterator;

    private:
        const ResTypeListIterator *_iter;
        const unsigned char *_data;
        const std::string _tid;

    protected:
        ResTypeEntry(const ResTypeListIterator *iter, const unsigned char *p)
            : _iter(iter), _data(p), _tid((const char *)p, 4)
        {
        }

    public:

        // raw memory accesses
        const unsigned char *_entry() const { return _data; }
        const unsigned char *_resList() const;
        std::size_t _numRes() const
        {
            return get_be_u16(&_data[RFTLE_F_NUM_RES]) + 1;
        }

        const std::string &typeId () const { return _tid; }
#if 0
        ResourceIterator &getResourceList() const
        {
            return ResourceIterator(this, 
        }

        ResourceIterator &getResourceListEnd() const
        {
        }
#endif
};

std::ostream &operator<<(std::ostream &out, const ResTypeEntry &re)
{
    return out << re.typeId();
}

}

#endif // LIBMB_RESTYPEENTRY_HH
