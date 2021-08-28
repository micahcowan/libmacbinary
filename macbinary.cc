#include "macbinary.hh"

MacBinary::ResourceFork & MacBinary::getResourceFork()
{
    if (!_res) _res = new ResourceFork();
    return *_res;
}
