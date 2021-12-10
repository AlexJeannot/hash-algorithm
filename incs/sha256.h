#ifndef SHA256
# define SHA256

# include "./base.h"

typedef struct s_buffers
{
    u_int32_t a;
    u_int32_t b;
    u_int32_t c;
    u_int32_t d;
    u_int32_t e;
    u_int32_t f;
    u_int32_t g;
    u_int32_t h;
}       t_buffers;


/*
** AUXILIARY_FUNCTIONS.C
*/
u_int32_t ch(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t maj(u_int32_t x, u_int32_t y, u_int32_t z);
u_int32_t ssig0(u_int32_t x);
u_int32_t ssig1(u_int32_t x);
u_int32_t bsig0(u_int32_t x);
u_int32_t bsig1(u_int32_t x);

/*
** CONST.C
*/
extern const u_int32_t computed_constants[64];

/*
** DIGEST.C
*/
void init_buffers(t_buffers *buffers);
void store_buffers(t_buffers *buffers, t_buffers *save_buffers);
void add_buffers(t_buffers *buffers, t_buffers *save_buffers);
void swap_buffers(t_buffers *buffers, u_int32_t t1, u_int32_t t2);
void process_round(t_buffers *buffers, u_int32_t block, u_int32_t count);
char* process_msg(t_message *msg);


#endif