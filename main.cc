#include "macbinary.hh"

using namespace libmacbinary;

int main(void) {
    MacBinary mb(0, 0);
    MacBinary::ResourceFork &rf = mb.getResourceFork();
}
