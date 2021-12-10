#include "../../incs/md5.h"

/*
** For signed integer
** & on right shift because MSB of 1 set 1 on every bit
*/

/*
** Swap endianness function for unsigned 16 bits integer
*/
u_int16_t swap_uint_16(u_int16_t val)
{
    val = (val << 8) | (val >> 8);
    return (val);
}

/*
** Swap endianness function for signed 16 bits integer
*/
int16_t swap_int_16(int16_t val)
{
    val = (val << 8) | ((val >> 8) & 0x00FF);
    return (val);
}

/*
** Swap endianness function for unsigned 32 bits integer
*/
u_int32_t swap_uint_32(u_int32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    val = (val << 16) | (val >> 16);
    return (val);
}

/*
** Swap endianness function for signed 32 bits integer
*/
int32_t swap_int_32(int32_t val)
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0x00FF00FF);
    val = (val << 16) | ((val >> 16) & 0x0000FFFF );
    return (val);
}

/*
** Swap endianness function for unsigned 64 bits integer
*/
u_int64_t swap_uint_64(u_int64_t val)
{
    val = ((val << 8) & 0xFF00FF00FF00) | ((val >> 8) & 0x00FF00FF00FF);
    val = ((val << 16) & 0xFFFF0000FFFF0000) | ((val >> 16) & 0x0000FFFF0000FFFF);
    val = (val << 32) | (val >> 32);
    return (val);
}

/*
** Swap endianness function for signed 64 bits integer
*/
int64_t swap_int_64(int64_t val)
{
    val = ((val << 8) & 0xFF00FF00FF00) | ((val >> 8) & 0x00FF00FF00FF);
    val = ((val << 16) & 0xFFFF0000FFFF0000) | ((val >> 16) & 0x0000FFFF0000FFFF);
    val = (val << 32) | ((val >> 32) & 0x00000000FFFFFFFF);
    return (val);
}