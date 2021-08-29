#include "macbinary.hh"
#include "ressectioniter.hh"
#include "offsets.hh"

using namespace libmacbinary;

using std::uint16_t;
using std::size_t;

MacBinary::ResourceFork & MacBinary::getResourceFork()
{
    const unsigned char *resStart;
    std::size_t resLen;

    // XXX confirm we don't run past _len
    // XXX MATH US WRONG: data should be padded to 128-byte boundary
    resStart = _data + MB_HEADER_LENGTH + _getU16(MB_F_DATA_FORK_LENGTH);
    resLen   = _getU16(MB_F_RES_FORK_LENGTH);
    // XXX ensure multiples of 128

    if (!_res) _res = new ResourceFork(this, resStart, resLen);
    return *_res;
}

ResSectionIter MacBinary::ResourceFork::getSections() {
    return ResSectionIter(this, _tlStart_p() + RFTL_F_START_OF_ENTRIES);
}

ResSectionIter MacBinary::ResourceFork::getSectionsEnd()
{
    return ResSectionIter(this, _tlStart_p() + RFTL_F_START_OF_ENTRIES + (_numTypes() * RFTLE_SIZE));
}

const unsigned char *MacBinary::ResourceFork::_mapStart_p()
{
    return _data + _getU32(RF_F_RES_MAP_OFF);
}

const unsigned char *MacBinary::ResourceFork::_tlStart_p()
{
    return _mapStart_p() + _getU16((_mapStart_p() - _data) + RFM_F_TYPE_LIST_OFF);
}

size_t MacBinary::ResourceFork::_numTypes()
{
    return _getU16((_tlStart_p() - _data) + RFTL_F_NUM_TYPES) + 1;
}
