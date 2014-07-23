
#include "BinaryParsing.hpp"


////////////////////////
///  SIGNED,         ///
///  2's complement  ///
////////////////////////

//TODO: NOT IMPLEMENTED YET
int32_t bendian::read_32(std::istream& f)
{
    return -1;
}
int16_t bendian::read_16(std::istream& f)
{
    return -1;
}
int8_t bendian::read_8(std::istream& f)
{
    return -1;
}

//////////////////
///  UNSIGNED  ///
//////////////////

uint32_t bendian::read_u32(std::istream& f)
{
    uint32_t val;
    uint8_t bytes[4];
    f.read((char*)bytes, 4);

    //"shifts are backwards. They must grow in size as the index shrinks"
    val = bytes[3] | (bytes[2] << 8) | (bytes[1] << 16) | (bytes[0] << 24);
    return val;
}
uint16_t bendian::read_u16(std::istream& f)
{
    uint16_t val;
    uint8_t bytes[2];
    f.read((char*)bytes, 2);
    val = bytes[1] | (bytes[0] << 8);
    return val;
}
uint8_t bendian::read_u8(std::istream& f)
{
    uint8_t val;
    uint8_t bytes[1];
    f.read((char*)bytes, 1);
    val = bytes[0];
    return val;
}

