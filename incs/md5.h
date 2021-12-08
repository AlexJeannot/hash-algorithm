#ifndef MD5
# define MD5

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

# define FALSE 0
# define TRUE 1
# define ERROR 2

typedef struct  s_message
{
    char *raw_content;
    char *fmt_content;
    u_int64_t rc_size;
    u_int64_t fc_size;
    u_int64_t cc_size;
    int32_t fd;

}               t_message;

typedef struct s_buffers
{
    u_int32_t a;
    u_int32_t b;
    u_int32_t c;
    u_int32_t d;

}       t_buffers;

/*
** ANNEXES.C
*/
size_t		ft_strlen(const char *s);
u_int8_t bytes_join(t_message *msg, char *buf, u_int64_t buf_length);


/*
** CLEAN.C
*/
void clean_msg(t_message *msg);


/*
** ERROR.C
*/
void fatal_error(char *reason);


/*
** FILE.C
*/
void get_file(t_message *msg, char *path);
void get_file_content(t_message *msg);


/*
** PADDING.C
*/
void format_msg(t_message *msg);


/*
** SWAP.C
*/
u_int16_t swapuInt16(u_int16_t val);
int16_t swapInt16(int16_t val);
u_int32_t swapuInt32(u_int32_t val);
int32_t swapInt32(int32_t val);
u_int64_t swapuInt64(u_int64_t val);
int64_t swapInt64(int64_t val);



/*
** CONST.C
*/
extern const u_int32_t constants[64];
extern const u_int32_t computed_constants[64];
extern const u_int32_t blocks_constants[64];



typedef u_int32_t(*round_function)(u_int32_t, u_int32_t, u_int32_t);

u_int32_t f(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t g(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t h(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t i(u_int32_t x, u_int32_t y, u_int32_t z);


#endif