#include "../../incs/md5.h"

int32_t get_file(char *path)
{
    int32_t fd;

    if ((fd = open(path, O_RDONLY)) == -1)
        return (-1);
    return (fd);
}

t_message *get_file_content(int32_t fd)
{
    char buf[1024];
    ssize_t ret;
    t_message *msg;

    bzero(&buf[0], 1024);
    msg = allocate_msg();
    if (fd >= 0)
    {
        while ((ret = read(fd, buf, 1023)) > 0) {
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
    else
        msg->nofile = TRUE;

    return (msg);
}

void set_file_context(t_message *msg, char *path)
{
    msg->src_type = SRC_FILE;
    if (!(msg->src = (char *)malloc(strlen(path) + 1)))
        fatal_error("malloc");
    bzero(msg->src, (strlen(path) + 1));
    strncpy(msg->src, path, strlen(path));
}

void process_file(char *path)
{
    int32_t fd;
    t_message *msg;

    fd = get_file(path);
    msg = get_file_content(fd);
    set_file_context(msg, path);
    if (fd > 0 && close(fd) == -1)
        fatal_error("fd"); // todo 
}