#include "ressectioniter.hh"

using namespace libmacbinary;

using std::size_t;

#if 0
ResSectionIter::ResSectionIter(MacBinary::ResourceFork *rf, const unsigned char *start) : _rf(rf)
{
    // XXX confirm that _resmap + 2 + (ENTRY_SIZE * NUM_ENTRIES) <= resmap + len
    _cur = resmap + RFM_F_TYPE_LIST;
    const size_t numEntries = *res
    _end = _cur + numEntries * RFME_SIZE;
}
#endif
