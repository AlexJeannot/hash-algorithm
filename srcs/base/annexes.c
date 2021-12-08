#include "../../incs/md5.h"

size_t		ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
    if (s == NULL) {
        while (s[i])
            i++; 
    }
	return (i);
}

u_int8_t bytes_join(t_message *msg, char *buf, u_int64_t buf_length)
{
    char *new_msg;

    if (!(new_msg = (char *)malloc(msg->rc_size + buf_length + 1)))
        return (ERROR);
    
    memcpy(new_msg, msg->raw_content, msg->rc_size);
    memcpy(&(new_msg[msg->rc_size]), buf, buf_length);

    if (msg->raw_content)
        free(msg->raw_content);
    msg->raw_content = new_msg;
    msg->rc_size += buf_length;

    return (TRUE);
}