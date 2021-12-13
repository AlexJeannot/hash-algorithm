#include "../../incs/md5.h"

char* md5(t_message *msg)
{
    char *hash;
    
    format_msg(msg, FALSE);
    hash = process_msg_md5(msg);
    clean_msg(msg);
    
    return (hash);
}