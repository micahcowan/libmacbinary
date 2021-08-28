#include "macbinary.hh"

using namespace libmb;

int main(void) {
    MacBinary mb(0, 0);
    MacBinary::ResourceFork &rf = mb.getResourceFork();
}
