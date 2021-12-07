#include "../../incs/md5.h"

size_t		ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
    if (s == NULL)
        return (0);
	while (s[i])
		i++;
	return (i);
}

char *retrieve_msg(char *msg, char *buf)
{


    char *new_msg;
    int new_count;

    if ((new_msg = (char *)malloc((ft_strlen(msg) + ft_strlen(buf) + 1 ) * sizeof(char))) == NULL) {
        printf("Error in malloc new message\n");
        if (msg)
            free(msg);
        exit(1);
    }

    new_count = 0;
    if (msg)
        for (size_t count = 0; count < ft_strlen(msg); count++) {
            new_msg[new_count] = msg[count];
            new_count++;
        }
    

    
    for (size_t count = 0; count < ft_strlen(buf); count++) {
            new_msg[new_count] = buf[count];
            new_count++;
        }


    if (msg)
        free(msg);
    return (new_msg);
}

void construct_msg(t_message *msg) {

    msg->fc_size = msg->rc_size + 8 + (64 - ((msg->rc_size + 8) % 64));

    if (!(msg->fmt_content = (char *)malloc(msg->fc_size * sizeof(char)))) {
        printf("Error in malloc final message\n");
        if (msg)
            free(msg);
        exit(1);
    }

    memcpy(msg->fmt_content, msg->raw_content, msg->rc_size);
    msg->fmt_content[msg->rc_size] = 0b10000000;
    *(uint64_t *)&(msg->fmt_content[msg->fc_size - 8]) = msg->rc_size * 8;
    //msg->fmt_content[0] = swapuInt64(msg->rc_size);
}

int main(int argc, char **argv) 
{
    char* file;
    int fd;
    int ret;
    t_message msg;

    bzero(&msg, sizeof(t_message));
    if (argc <= 1 || argc > 2) {
        printf("Need an argument\n");
        exit(1);
    }

    file =  argv[1];
    printf("FILE is %s\n", file);

    fd = open(file, O_RDONLY);
    if (fd == -1) {
        printf("Error in file opening\n");
        exit(1);
    }

    char buf[1024];

    bzero(&buf[0], 1024);


    while ((ret = read(fd, buf, 1023)) > 0) {
        buf[ret] = '\0';
        retrieve_msg(&msg.raw_content, &buf[0]);
        bzero(&buf[0], 1024);
    }
    if (ret == -1) {
        printf("Error in file reading\n");
        if (tmp_msg)
            free(tmp_msg);
        exit(1);
    }
    msg.raw_content = tmp_msg;
    msg.rc_size = strlen(tmp_msg);

    construct_msg(&msg);

    printf("MSG = %s\n", msg.raw_content);
    if (msg.raw_content)
        free(msg.raw_content);

    system("leaks ft_md5");
    return (0);
}