#include "../../incs/md5.h"

int main(int argc, char **argv) 
{
    t_message msg;

    bzero(&msg, sizeof(t_message));

    if (argc <= 1 || argc > 2) {
        printf("Need an argument\n");
        exit(1);
    }

    get_file(&msg, argv[1]);
    get_file_content(&msg);
    // printf("RAW CONTENT = %s\n", msg.raw_content);

    format_msg(&msg);
    // printf("FMT CONTENT = %s\n", msg.fmt_content);

    // printf("\n\n");
    // char c;
    // for (int count = 0; count < 64 ; count++)
    // {
    //     c = msg.fmt_content[count];
    //     for (int bit = 0; bit < 8; bit++)
    //     {
    //         printf("%d", c & 0b00000001);
    //         c = c >> 1;
    //     }
    //     printf(" ");
    // }
    // printf("\n\n");


    process_msg(&msg);

    clean_msg(&msg);
    return (0);
}