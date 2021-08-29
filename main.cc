#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "macbinary.hh"
#include "ressectioniter.hh"

using namespace libmacbinary;

using std::cout;
using std::endl;
using std::hex;
using std::dec;

int main(void) {
    size_t sz = 40320;
    int fd = open("fbapp.bin", O_RDONLY);
    if (fd == -1) {
        cout << "Die." << endl;
        return 1;
    }
    unsigned char *mem = (unsigned char *)mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    cout << "Start of file in memory: " << (void*)mem << endl;

    MacBinary mb(mem, sz);
    MacBinary::ResourceFork &rf = mb.getResourceFork();
    cout << "Start of res fork: " << hex << rf._start() << endl;
    cout << "Start of res map: " << hex << rf._mapStart() << endl;
    cout << "Start of res type list: " << hex << rf._tlStart() << endl;
    cout << dec << rf._numTypes() << " items in list:" << endl;

    auto end = rf.getSectionsEnd();
    for (auto i = rf.getSections(); i != end; ++i) {
        cout << "  " << *i << endl;
    }
}
