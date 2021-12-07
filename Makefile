# VARIABLES
GREEN 	= \033[38;5;40m
RESET 	= \033[0m
MD5 		= ft_md5
OTOOL 	= ft_otool

# COMPILATION
CC 		= gcc
FLAGS 	= -Wall -Wextra -Werror
RM 		= rm -rf


# DIRECTORIES
DSRCS		= ./srcs/
MD5_DIR		= md5/
#OTOOL_DIR 	= otool/
#BASE_DIR 	= base/

MD5_DOBJS	= ./comp/md5/
#OTOOL_DOBJS	= ./comp/otool/
#BASE_DOBJS	= ./comp/base/


# SOURCES
MD5_SRCS 	= 	md5.c	\
				swap.c

#OTOOL_SRCS 	= 	otool.c
#BASE_SRCS 	= 	clear.c		\
				control.c	\
				display.c	\
				exit.c 		\
				fat.c		\
				lib.c		\
				parse.c		\
				resources.c	\
				segment.c	\
				swap.c		\
				symbol.c	\
				text.c

# OBJS
MD5_OBJS 	= $(MD5_SRCS:%.c=$(MD5_DOBJS)%.o)
#OTOOL_OBJS 	= $(OTOOL_SRCS:%.c=$(OTOOL_DOBJS)%.o)
#BASE_OBJS 	= $(BASE_SRCS:%.c=$(BASE_DOBJS)%.o)


#H EADER FILE
#HEADER = ./incs/nm_otool.h
HEADER = ./incs/md5.h


# MAKE
#all: $(NM) $(OTOOL)
all: $(MD5)


# COMPILATION
$(MD5): $(MD5_OBJS) #$(BASE_OBJS)
#	$(CC) $(FLAGS) $(NM_OBJS) $(BASE_OBJS) -o $(NM)
	$(CC) $(FLAGS) $(MD5_OBJS) -o $(MD5)
	echo "$(GREEN)MD5 DONE ✔$(RESET)"

#$(OTOOL): $(OTOOL_OBJS) $(BASE_OBJS)
#	$(CC) $(FLAGS) $(OTOOL_OBJS) $(BASE_OBJS) -o $(OTOOL)
#	echo "$(GREEN)OTOOL DONE ✔$(RESET)"

$(MD5_OBJS): | $(MD5_DOBJS)
#$(OTOOL_OBJS): | $(OTOOL_DOBJS)
#$(BASE_OBJS): | $(BASE_DOBJS)

$(MD5_DOBJS)%.o: $(DSRCS)$(MD5_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

#$(OTOOL_DOBJS)%.o: $(DSRCS)$(OTOOL_DIR)%.c $(HEADER)
#	$(CC) $(FLAGS) -c $< -o $@

#$(BASE_DOBJS)%.o: $(DSRCS)$(BASE_DIR)%.c $(HEADER)
#	$(CC) $(FLAGS) -c $< -o $@


# OBJECT FILE DIRECTORY CREATION
$(MD5_DOBJS):
	mkdir -p $(MD5_DOBJS)

#$(OTOOL_DOBJS):
#	mkdir -p $(OTOOL_DOBJS)

#$(BASE_DOBJS):
#	mkdir -p $(BASE_DOBJS)


# CLEAR
clean:
	$(RM) ./comp

fclean: clean
#	$(RM) $(NM) $(OTOOL)
	$(RM) $(MD5)

re: fclean all

.PHONY: all clean fclean re
.SILENT: all $(MD5)