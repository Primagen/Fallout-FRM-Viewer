
#ifndef BINARY_PARSING_HPP
#define BINARY_PARSING_HPP

#include <cstdint>
#include <fstream>

/**  BINARY PARSING
 *   See Disch's tutorial: http://www.cplusplus.com/articles/DzywvCM9/
 *
 * This header declares useful functions to use
 * while reading a binary file.
 * The read_N functions read and return the next N-bits
 * of the given file.
 */

/**
 * Big-Endian namespace
 * Fallout FRM files need to be parsed in this format
 * Note that the read_8 functions are redundant
 * because the endianness doesn't matter for just 1 byte.
 */
namespace bendian {
    /**
     * NOT IMPLEMENTED YET
     * Read signed values of a given size.
     * These are in 2's complement format
     */
    int32_t read_32(std::istream& f);
    int16_t read_16(std::istream& f);
    int8_t  read_8(std::istream& f);

    /**
     * Read unsigned values for a given size
     */
    uint32_t read_u32(std::istream& f);
    uint16_t read_u16(std::istream& f);
    uint8_t  read_u8(std::istream& f);
}

/**
 * Little-Endian namespace
 * Not used yet
 */
namespace lendian {
    //Signed:

    //Unsigned:
}

#endif // BINARY_PARSING_HPP
