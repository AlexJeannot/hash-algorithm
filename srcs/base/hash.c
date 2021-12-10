#include "../../incs/base.h"

char *uint_to_hex(u_int64_t number)
{
    u_int64_t tmp_number;
    int16_t number_char;
    char *output;

    tmp_number = number;
    number_char = 1;
    while (tmp_number /= 16)
        number_char++;
    if (!(output = malloc(number_char)))
        exit(1); //todo

    number_char--;
    for (; number_char >= 0; number_char--) {
        if (number % 16 >= 10)
            output[number_char] = number % 16 - 10 + 'a';
        else
            output[number_char] = number % 16 + '0';
        number /= 16;
    }
    return (output);
}

char *build_hash(void *buffers, u_int32_t nb_words, u_int8_t swap)
{
    char        *hash;
    u_int32_t   *buffer;
    u_int8_t    nb_chars;

    nb_chars = (nb_words * 8) + 1;
    if (!(hash = (char *)malloc(nb_chars)))
        exit(1);
    bzero(hash, nb_chars);

    for (u_int32_t count = 0; count < nb_words; count++) {
        buffer = ((u_int32_t *)(buffers)) + count;
        if (swap == TRUE)
            strncat(hash, uint_to_hex(swap_uint_32(*buffer)), 8);
        else
            strncat(hash, uint_to_hex(*buffer), 8);
    }

    return (hash);
}