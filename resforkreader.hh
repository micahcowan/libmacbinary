#ifndef LIBMB_RESFORKREADER_HH
#define LIBMB_RESFORKREADER_HH

#include <cstdlib>

#include "restypelistiter.hh"
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

        ResTypeListIterator getSections() const
        {
            return ResTypeListIterator(this, _typeListEntriesStart());
        }

        ResTypeListIterator getSectionsEnd() const
        {
            return ResTypeListIterator(this, _typeListEntriesEnd());
        }

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



}

#endif // LIBMB_RESFORKREADER_HH
