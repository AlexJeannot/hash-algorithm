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
    printf("RAW CONTENT = %s\n", msg.raw_content);

    format_msg(&msg);
    printf("FMT CONTENT = %s\n", msg.fmt_content);

    clean_msg(&msg);
    return (0);
}