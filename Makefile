# VARIABLES
GREEN 	= \033[38;5;40m
RESET 	= \033[0m
MD5 		= ft_md5
SHA256 	= ft_sha256

# COMPILATION
CC 		= gcc
FLAGS 	= -Wall -Wextra -Werror
RM 		= rm -rf


# DIRECTORIES
DSRCS		= ./srcs/
MD5_DIR		= md5/
SHA256_DIR 	= sha256/
BASE_DIR 	= base/

MD5_DOBJS	= ./comp/md5/
SHA256_DOBJS	= ./comp/sha256/
BASE_DOBJS	= ./comp/base/


# SOURCES
MD5_SRCS 	= 	auxiliary_functions.c	\
				const.c					\
				digest.c				\
				md5.c
				

SHA256_SRCS 	= 	auxiliary_functions.c	\
					const.c					\
					digest.c				\
					sha256.c	

BASE_SRCS 	= 	annexes.c	\
				clean.c		\
				error.c		\
				file.c		\
				hash.c		\
				padding.c	\
				swap.c		

# OBJS
MD5_OBJS 	= $(MD5_SRCS:%.c=$(MD5_DOBJS)%.o)
SHA256_OBJS 	= $(SHA256_SRCS:%.c=$(SHA256_DOBJS)%.o)
BASE_OBJS 	= $(BASE_SRCS:%.c=$(BASE_DOBJS)%.o)


#H EADER FILE
#HEADER = ./incs/sha256.h
HEADER =	./incs/base.h	\
			./incs/md5.h	\
			./incs/sha256.h


# MAKE
#all: $(NM) $(SHA256)
all: $(MD5) $(SHA256)


# COMPILATION
$(MD5): $(MD5_OBJS) $(BASE_OBJS)
	$(CC) $(FLAGS) $(MD5_OBJS) $(BASE_OBJS) -o $(MD5)
#	$(CC) $(FLAGS) $(MD5_OBJS) -o $(MD5)
	echo "$(GREEN)MD5 DONE ✔$(RESET)"

$(SHA256): $(SHA256_OBJS) $(BASE_OBJS)
	$(CC) $(FLAGS) $(SHA256_OBJS) $(BASE_OBJS) -o $(SHA256)
	echo "$(GREEN)SHA256 DONE ✔$(RESET)"

$(MD5_OBJS): | $(MD5_DOBJS)
$(SHA256_OBJS): | $(SHA256_DOBJS)
$(BASE_OBJS): | $(BASE_DOBJS)

$(MD5_DOBJS)%.o: $(DSRCS)$(MD5_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(SHA256_DOBJS)%.o: $(DSRCS)$(SHA256_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(BASE_DOBJS)%.o: $(DSRCS)$(BASE_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@


# OBJECT FILE DIRECTORY CREATION
$(MD5_DOBJS):
	mkdir -p $(MD5_DOBJS)

$(SHA256_DOBJS):
	mkdir -p $(SHA256_DOBJS)

$(BASE_DOBJS):
	mkdir -p $(BASE_DOBJS)


# CLEAR
clean:
	$(RM) ./comp

fclean: clean
#	$(RM) $(NM) $(SHA256)
	$(RM) $(MD5) $(SHA256)

re: fclean all

.PHONY: all clean fclean re
.SILENT: all $(MD5) $(SHA256)