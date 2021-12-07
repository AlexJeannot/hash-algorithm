#ifndef MD5
# define MD5

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

typedef struct  s_message
{
    char *raw_content;
    char *fmt_content;
    uint64_t rc_size;
    uint64_t fc_size;

}               t_message;


uint16_t swapuInt16(uint16_t val);
int16_t swapInt16(int16_t val);
uint32_t swapuInt32(uint32_t val);
int32_t swapInt32(int32_t val);
uint64_t swapuInt64(uint64_t val);
int64_t swapInt64(int64_t val);


#endif