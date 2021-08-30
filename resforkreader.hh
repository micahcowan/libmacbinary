#ifndef LIBMB_RESFORKREADER_HH
#define LIBMB_RESFORKREADER_HH

#include <iterator>
#include <string>
#include <ostream>

#include <cstdlib>

#include "offsets.hh"
#include "bigendian.hh"

namespace libmacbinary {

class ResTypeListIterator;

class ResForkReader {
    private:
        const unsigned char * const _data;
        const unsigned char * const _dataEnd;

    public:
        ResForkReader(const unsigned char *p, const unsigned char *e)
            : _data(p), _dataEnd(e)
            {}
        virtual ~ResForkReader() {}

        inline ResTypeListIterator getTypeList() const;
        inline ResTypeListIterator getTypeListEnd() const;

        // Various useful locations in a resource fork
        const unsigned char *_start() const { return _data; }
        const unsigned char *_mapStart() const
        {
            return _data + get_be_u32(&_data[RF_F_RES_MAP_OFF]);
        }
        const unsigned char *_typeList() const
        {
            return _mapStart() + get_be_u16(&(_mapStart())[RFM_F_TYPE_LIST_OFF]);
        }
        const unsigned char *_typeListEntriesStart() const
        {
            return _typeList() + RFTL_F_START_OF_ENTRIES;
        }
        const unsigned char *_typeListEntriesEnd() const
        {
            return _typeListEntriesStart() + (_numTypes() * RFTLE_SIZE);
        }
        std::size_t _numTypes() const
        {
            return get_be_u16(_typeList() + RFTL_F_NUM_TYPES) + 1;
        }
};

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

std::ostream &operator<<(std::ostream &out, const ResTypeEntry &re)
{
    return out << re.typeId();
}

// Inter-dependent member function definitions

inline ResTypeListIterator ResForkReader::getTypeList() const
{
    return ResTypeListIterator(this, _typeListEntriesStart());
}

inline ResTypeListIterator ResForkReader::getTypeListEnd() const
{
    return ResTypeListIterator(this, _typeListEntriesEnd());
}


} // libmacbinary

#endif // LIBMB_RESFORKREADER_HH
