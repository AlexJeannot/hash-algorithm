#ifndef MD5
# define MD5

# include "./base.h"

typedef struct s_buffers
{
    u_int32_t a;
    u_int32_t b;
    u_int32_t c;
    u_int32_t d;

}       t_buffers;

typedef u_int32_t(*round_function)(u_int32_t, u_int32_t, u_int32_t);


/*
** CONST.C
*/
extern const u_int32_t constants[64];
extern const u_int32_t computed_constants[64];
extern const u_int32_t blocks_constants[64];

/*
** AUXILIARY_FUNCTIONS.C
*/
u_int32_t f(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t g(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t h(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t i(u_int32_t x, u_int32_t y, u_int32_t z);

/*
** DIGEST.C
*/
void init_buffers(t_buffers *buffers);
void store_buffers(t_buffers *buffers, t_buffers *save_buffers);
void swap_buffers(t_buffers *buffers);
void add_buffers(t_buffers *buffers, t_buffers *save_buffers);
void process_round(t_buffers *buffers, u_int32_t block, u_int32_t round, u_int32_t count);
char* process_msg(t_message *msg);


#endif