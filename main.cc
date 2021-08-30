#include <iostream>
#include <iomanip>

#include <cstring>
#include <cerrno>
#include <cstdlib>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "macbinary.hh"
#include "resforkreader.hh"

using namespace libmacbinary;

using std::cerr;
using std::cout;
using std::endl;
using std::hex;
using std::dec;
using std::size_t;
using std::string;
using std::setfill;
using std::setw;

inline char saneChar(unsigned char c)
{
    // Assumes ASCII-compatible
    if (c >= 0x20 /* space */
        && c < 0x7F /* DEL */) {

        return (char)c;
    }
    else {
        return '.';
    }
}

class HexFormatter
{
    private:
        size_t count = 0;
        const size_t groupN;
        const size_t lineN;
        unsigned char *buf;
        std::ostream &out;

        void dumpBuffer(void)
        {
            cout << string(2*groupN + 1, ' ');
            for (size_t i = 0; i != count; ++i) {
                out << saneChar(buf[i]);
            }
        }
    public:
        HexFormatter(
            size_t groupN = 2,
            size_t lineN = 8,
            std::ostream &out = cout
            ) : groupN(groupN), lineN(lineN), out(out)
        {
            buf = new unsigned char[lineN];
        }

        virtual ~HexFormatter()
        {
            flush();
            delete[] buf;
        }

        virtual void printByte(unsigned char byte)
        {
            if (count % groupN == 0) cout << ' ';

            out << hex << setfill('0') << setw(2) << (int)byte;
            buf[count] = byte;
            ++count;

            if (count == lineN) flush();
        }

        virtual void flush(void)
        {
            if (count != 0) {
                dumpBuffer();
                cout << endl;
            }
            count = 0;
        }
};

void printError(const string &msg)
{
    cerr << msg << ": " << strerror(errno) << endl;
}

unsigned char *mmapFile(const char * const fileName, size_t *sz)
{
    unsigned char *mem = NULL;

    // Open the file
    errno = 0;
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        printError("Couldn't open file");
        return NULL;
    }

    // Get the file's size for mmap
    errno = 0;
    struct stat buf;
    int result = fstat(fd, &buf);
    if (result != 0) {
        printError("Couldn't stat file (so no mmap)");
        goto close_and_end;
    }
    *sz = buf.st_size;

    // Mmap the file
    errno = 0;
    mem = static_cast<unsigned char *>(mmap(NULL, *sz, PROT_READ, MAP_PRIVATE, fd, 0));
    if (mem == NULL) {
        printError("Couldn't mmap file");
        goto close_and_end;
    }

close_and_end:
    close(fd);
    return mem;
}

void printResFork(unsigned char * mem, size_t sz)
{
    cout << "Start of file in memory: " << (void*)mem << endl;

    const MacBinary mb(mem, sz);
    const unsigned char *rfs, *rfe;
    rfs = mb.getResourceFork();
    rfe = mb.getResourceForkEnd();
    const ResForkReader rf(rfs, rfe);

    cout << "Start of res fork: " << hex << (rf._start() - mem) << endl;

    // Application data
    const unsigned char *app, *appEnd;
    app     = rf._appDataStart();
    appEnd  = rf._appDataEnd();
    cout << "Application data in resource fork:" << endl;
    HexFormatter hf;
    const unsigned char *p;
    for (p = app; p != appEnd; ++p) {
        hf.printByte(*p);
    }
    hf.flush();
    cout << endl;

    cout << "Start of res map: " << hex << (rf._mapStart() - mem) << endl;
    cout << "Start of res type list: " << hex << (rf._typeList() - mem) << endl;
    cout << dec << rf.numTypes() << " items in list:" << endl;

    auto end = rf.getTypeListEnd();
    // iterate over resource types
    for (auto i = rf.getTypeList(); i != end; ++i) {
        ResTypeEntry e = *i;
        cout << "  " << e << " (" << dec << e.numResources() << ')' << endl;
        cout << "    reslist starts " << hex << (e._resList() - mem) << ':';
        cout << dec;
        // iterate over resources
        auto resEnd = e.getResourcesEnd();
        for (auto j = e.getResources(); j != resEnd; ++j)
        {
            cout << ' ' << (*j).id();
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char **argv) {
    unsigned char *mem;
    size_t sz;
    int status = 0;

    if (*argv != NULL) ++argv;   // Skip our program's name

    while (*argv != NULL) {
        cout << *argv << ":" << '\n' << endl;
        mem = mmapFile(*argv, &sz);
        if (mem) {
            printResFork(mem, sz);
            munmap(static_cast<void*>(mem), sz);
        }
        else {
            status = 1;
        }

        ++argv;
    }

    return status;
}
