#ifndef LIBMB_BIGENDIAN_HH
#define LIBMB_BIGENDIAN_HH

#include <cstdint>

static inline std::uint16_t get_be_u16(const unsigned char *p)
{
    return p[0] * 256 + p[1];
}

static inline std::uint32_t get_be_u32(const unsigned char *p)
{
    const unsigned char *pe = p + 4;
    std::uint32_t val = 0;
    for (; p != pe; ++p) {
        val <<= 8;
        val += *p;
    }
    return val;
}

#endif // LIBMB_BIGENDIAN_HH