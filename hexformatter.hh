// hexformatter.hh
//   formats arbitrary binary data, somewhat like hexdump/hd

#ifndef HEXFORMATTER_HH
#define HEXFORMATTER_HH

#include <iostream>
#include <iomanip>
#include <string>

#include <cstdlib>

using std::cout;
using std::endl;
using std::setfill;
using std::hex;
using std::setw;
using std::string;

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

        void padOutLine(void)
        {
            for (size_t c = count; c != lineN; ++c) {
                if (c % groupN == 0) cout << ' ';
                cout << "  ";
            }
        }
    public:
        HexFormatter(
            size_t groupN = 2,
            size_t lineN = 16,
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
                padOutLine();
                dumpBuffer();
                cout << endl;
            }
            count = 0;
        }
};

#endif // HEXFORMATTER_HH
