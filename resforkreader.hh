#ifndef LIBMB_RESFORKREADER_HH
#define LIBMB_RESFORKREADER_HH

#include <iterator>
#include <string>
#include <ostream>

#include <cstdlib>
#include <cstdint>

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
        const unsigned char *_appDataStart() const { return _data + RF_APP_DATA_OFF; }
        const unsigned char *_appDataEnd() const { return _appDataStart() + RF_APP_DATA_LENGTH; }
        const unsigned char *_mapStart() const
        {
            return _data + get_be_u32(&_data[RF_F_RES_MAP_OFF]);
        }
        const unsigned char *_typeList() const
        {
            return _mapStart() + get_be_u16(_mapStart() + RFM_F_TYPE_LIST_OFF);
        }
        const unsigned char *_typeListEntriesStart() const
        {
            return _typeList() + RFTL_F_START_OF_ENTRIES;
        }
        const unsigned char *_typeListEntriesEnd() const
        {
            return _typeListEntriesStart() + (numTypes() * RFTLE_SIZE);
        }
        std::size_t numTypes() const
        {
            return get_be_u16(_typeList() + RFTL_F_NUM_TYPES) + 1;
        }
        const unsigned char *_nameListStart() const
        {
            return _mapStart() + get_be_u16(_mapStart() + RFM_F_NAME_LIST_OFF);
        }
};

class ResourceIterator;

class ResTypeEntry
{
    friend class ResTypeListIterator;

    private:
        const ResForkReader *_rf;
        const unsigned char *_data;
        const std::string _tid;

    protected:
        ResTypeEntry(const ResForkReader *rf, const unsigned char *p)
            : _rf(rf), _data(p), _tid((const char *)p, 4)
        {
        }

    public:
        inline const ResForkReader   &getReader() const;

        // raw memory accesses
        const unsigned char *_entry() const { return _data; }
        const unsigned char *_resList() const
        {
            return getReader()._typeList()
                + get_be_u16(&_data[RFTLE_F_REF_LIST_OFF]);
        }

        std::size_t numResources() const
        {
            return get_be_u16(&_data[RFTLE_F_NUM_RES]) + 1;
        }

        const std::string &typeId () const { return _tid; }
        inline ResourceIterator getResources() const;
        inline ResourceIterator getResourcesEnd() const;
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

        const ResForkReader &getReader() const
        {
            return *_rf;
        }

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
            return ResTypeEntry(_rf, _cur);
        }
};

class Resource;

class ResourceIterator :
    std::iterator<std::forward_iterator_tag, Resource>
{
    friend class ResTypeEntry;

    private:
        const ResForkReader *_rf;
        const unsigned char *_cur;
    protected:
        ResourceIterator(const ResForkReader *rf, const unsigned char *p)
            : _rf(rf), _cur(p)
            {}

    public:
        bool operator== (const ResourceIterator &other) const
        {
            return (_rf == other._rf) && (_cur == other._cur);
        }

        bool operator!= (const ResourceIterator &other) const
        {
            return !(*this == other);
        }

        ResourceIterator operator++()
        {
            _cur += RF_RES_SIZE;
            return *this;
        }

        inline const Resource operator*() const;
};

class Resource
{
    friend class ResourceIterator;
    private:
        const ResForkReader *_rf;
        const unsigned char *_data;
    protected:
        Resource(const ResForkReader *rf, const unsigned char *p)
            : _rf(rf), _data(p)
        { }
    public:
        std::int16_t id() const
        {
            return get_be_i16(_data + RF_RES_F_ID);
        }

        const std::string name() const
        {
            std::int16_t nameOff = get_be_i16(_data + RF_RES_F_NAME_OFF);
            if (nameOff == -1)
                return std::string("");
            const unsigned char *n = _rf->_nameListStart() + nameOff;
            // First byte is length, and then the string
            return std::string((const char *)n+1, *n);
        }
};

// Util fns

std::ostream &operator<<(std::ostream &out, const ResTypeEntry &re)
{
    return out << re.typeId();
}

// Inter-dependent member function definitions

//   ResForkReader
inline ResTypeListIterator ResForkReader::getTypeList() const
{
    return ResTypeListIterator(this, _typeListEntriesStart());
}

inline ResTypeListIterator ResForkReader::getTypeListEnd() const
{
    return ResTypeListIterator(this, _typeListEntriesEnd());
}

//    ResTypeEntry
inline const ResForkReader &ResTypeEntry::getReader() const
{
    return *_rf;
}

inline ResourceIterator ResTypeEntry::getResources() const
{
    return ResourceIterator(_rf, _resList());
}

inline ResourceIterator ResTypeEntry::getResourcesEnd() const
{
    return ResourceIterator(_rf, _resList() + (numResources() * RF_RES_SIZE));
}

//    ResourceIterator
inline const Resource ResourceIterator::operator*() const
{
    return Resource(_rf, _cur);
}

} // libmacbinary

#endif // LIBMB_RESFORKREADER_HH
