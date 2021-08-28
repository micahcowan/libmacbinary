#include "macbinary.hh"

typedef unsigned char uchar;
typedef const unsigned char UCHAR;

int main(void) {
    MacBinary<UCHAR *> mb(0, 0);
    MacBinary<UCHAR *>::ResourceFork &rf = mb.getResourceFork();
}
