#include "../../incs/md5.h"

int32_t     get_file(char *path)
{
    int32_t fd;

    fd = open(path, O_RDONLY);
    return (fd);
}

t_message   *get_file_content(int32_t fd)
{
    t_message   *msg;
    ssize_t     ret;
    char        buf[1024];

    ft_bzero(&buf[0], 1024);
    msg = allocate_msg();
    if (fd >= 0)
    {
        while ((ret = read(fd, buf, 1023)) > 0) {
            buf[ret] = '\0';
            bytes_join(msg, &buf[0], ret);
            ft_bzero(&buf[0], 1024);
        }
        if (ret == -1)
            fatal_error("file reading");
    }
    else
        msg->nofile = TRUE;

    return (msg);
}

void        set_file_context(t_message *msg, char *path)
{
    msg->src_type = SRC_FILE;

    if (!(msg->src = (char *)malloc(ft_strlen(path) + 1)))
        fatal_error("file source memory allocation");
    ft_bzero(msg->src, (ft_strlen(path) + 1));

    ft_strncpy(msg->src, path, ft_strlen(path));
}

void        process_file(char *path)
{
    t_message   *msg;
    int32_t     fd;

    fd = get_file(path);
    msg = get_file_content(fd);
    set_file_context(msg, path);
    if (fd > 0 && close(fd) == -1)
        fatal_error("file descriptor closing");
}