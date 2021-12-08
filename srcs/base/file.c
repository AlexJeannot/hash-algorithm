#include "../../incs/md5.h"

void get_file(t_message *msg, char *path)
{
    if ((msg->fd = open(path, O_RDONLY)) == -1)
        fatal_error("File opening");
}

void get_file_content(t_message *msg)
{
    char buf[1024];
    ssize_t ret;

    bzero(&buf[0], 1024);

    while ((ret = read(msg->fd, buf, 1023)) > 0) {
        buf[ret] = '\0';
        if (bytes_join(msg, &buf[0], ret) == ERROR) {
            clean_msg(msg);
            fatal_error("Message bytes joining");
        }
        bzero(&buf[0], 1024);
    }
    if (ret == -1) {
        clean_msg(msg);
        fatal_error("File reading");
    }
}