#ifndef BASE
# define BASE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>

# define FALSE 0
# define TRUE 1
# define ERROR 2
# define ALGO_MD5 5
# define ALGO_SHA256 6

# define SRC_STDIN 7
# define SRC_FILE 8
# define SRC_ARG 9

typedef struct  s_message
{
    char *raw_content;
    char *fmt_content;
    char *src;
    u_int8_t src_type;
    u_int64_t rc_size;
    u_int64_t fc_size;
    u_int64_t cc_size;
    u_int8_t    nofile;
    char *hash;
    struct  s_message *next;
}               t_message;

typedef struct s_args
{
    u_int8_t algorithm;
    u_int8_t p;
    u_int8_t q;
    u_int8_t r;

}       t_args;

extern t_message *list_msg;

/*
** ANNEXES.C
*/
size_t		ft_strlen(const char *s);
u_int8_t bytes_join(t_message *msg, char *buf, u_int64_t buf_length);

/*
** BITS.C
*/
u_int32_t rotate_left(u_int32_t x, u_int32_t offset);
u_int32_t rotate_right(u_int32_t x, u_int32_t offset);
u_int32_t shift_right(u_int32_t x, u_int32_t offset);

/*
** CLEAN.C
*/
void clean_msg(t_message *msg);


/*
** ERROR.C
*/
void fatal_error(char *reason);
void args_error(char *reason, char *input);


/*
** FILE.C
*/
// void get_file(t_message *msg, char *path);
// void get_file_content(t_message *msg);
t_message *get_file_content(int32_t fd);
void process_file(char *path);

/*
** HASH.C
*/
char *uint_to_hex(u_int64_t number);


/*
** PADDING.C
*/
void format_msg(t_message *msg, u_int8_t swap);
void build_hash(t_message *msg, void *buffers, u_int32_t nb_words, u_int8_t swap);


/*
** SWAP.C
*/
u_int16_t swap_uint_16(u_int16_t val);
int16_t swap_int_16(int16_t val);
u_int32_t swap_uint_32(u_int32_t val);
int32_t swap_int_32(int32_t val);
u_int64_t swap_uint_64(u_int64_t val);
int64_t swap_int_64(int64_t val);

void md5(t_message *msg);
void sha256(t_message *msg);

void parse_args(int nb_args, char **list_args, t_args *args);
t_message *allocate_msg(void);
void display_help(void);
void display_hash(t_message *msg, t_args *args);


#endif