# CC			= gcc

# SCHOOL		= $(HOME)/.brew

# HOME		= usr/local

# CFLAGS		= -Wall -Werror -Werror

# # FLAGS		= -ltermcap -lreadline -L/$(SCHOOL)/Cellar/readline/8.1/lib -I/$(SCHOOL)/Cellar/readline/8.1/include - для мака

# FLAGS		= -ltermcap -lreadline -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include

# NAME		= miniparser

# SRCS		= *.c

# OBJS		= $(SRCS:.c=.o)

# HEADER		= miniparser.h

# LIBFT		= libft/libft.a

# all: 		$(NAME)

# %.o: %.c
# 			$(CC) $(CFLAGS) -c $^ -o $@

# $(NAME): 	$(OBJS) $(SRCS) Makefile $(HEADER) $(LIBFT)
# 			$(CC) $(CFLAGS) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
# $(LIBFT):
# 			cd libft && make && make bonus

# clean: 
# 			rm -f $(OBJS)
# 			cd libft && make clean
# fclean: 	clean
# 			rm -f $(NAME)
# 			cd libft && make fclean
# re: 		fclean all

# .PHONY: 	all clean fclean re

SRCS		=	${wildcard *.c}

OBJS		=	$(SRCS:.c=.o)	

HEADS		=	miniparser.h

LIBNAME		=	libft.a

LIBPATH		=	libft/

LIB			=	$(addprefix $(LIBPATH), $(LIBNAME))

NAME		=	miniparser

GCC			=	gcc -g -MMD -Wall -Wextra -Werror

RM			=	rm -f

READCLUDE	= -I/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/include

READLINE	= -lreadline -L -L/home/linuxbrew/.linuxbrew/Cellar/readline/8.1.2/lib $(READCLUDE)

%.o: 		%.c
			$(GCC) -c -I$(LIBPATH) $(READCLUDE) $< -o $@

$(NAME):	$(HEADS) $(LIB) $(OBJS)
			$(GCC) $(OBJS) $(LIB) -o $(NAME) $(READLINE)

all:		$(NAME)

$(LIB):		lib

lib:		
			@$(MAKE) -C $(LIBPATH)

clean:
			@$(MAKE) -C $(LIBPATH) clean
			$(RM) $(wildcard *.d)
			$(RM) $(OBJS)
			$(RM) $(B_OBJS)

fclean: 	clean
			@$(MAKE) -C $(LIBPATH) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re lib