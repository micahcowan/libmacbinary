#ifndef LIBMB_RESFORKREADER_HH
#define LIBMB_RESFORKREADER_HH

#include <cstdlib>

#include "restypelistiter.hh"
#include "bigendian.hh"

namespace libmacbinary {

class ResTypeListIterator;

class ResForkReader {
    friend class MacBinary;
    private:
        const unsigned char * const _data;
        const unsigned char * const _dataEnd;

    public:
        ResForkReader(const unsigned char *p, const unsigned char *e)
            : _data(p), _dataEnd(e)
            {}
        virtual ~ResForkReader() {}

        ResTypeListIterator getSections()
        {
            return ResTypeListIterator(this, _typeListEntriesStart());
        }

        ResTypeListIterator getSectionsEnd()
        {
            return ResTypeListIterator(this, _typeListEntriesEnd());
        }

        // Various useful locations in a resource fork
        const unsigned char *_start() { return _data; }
        const unsigned char *_mapStart()
        {
            return _data + get_be_u32(&_data[RF_F_RES_MAP_OFF]);
        }
        const unsigned char *_typeList()
        {
            return _mapStart() + get_be_u16(&(_mapStart())[RFM_F_TYPE_LIST_OFF]);
        }
        const unsigned char *_typeListEntriesStart()
        {
            return _typeList() + RFTL_F_START_OF_ENTRIES;
        }
        const unsigned char *_typeListEntriesEnd()
        {
            return _typeListEntriesStart() + (_numTypes() * RFTLE_SIZE);
        }
        std::size_t _numTypes()
        {
            return get_be_u16(_typeList() + RFTL_F_NUM_TYPES) + 1;
        }
};



}

#endif // LIBMB_RESFORKREADER_HH
