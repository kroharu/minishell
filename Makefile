NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g -fsanitize=address

USER = cgoth

READCLUDE	= -I~/.brew/Cellar/readline/8.1.2/include

READLINE	= -lreadline -L ~/.brew/Cellar/readline/8.1.2/lib $(READCLUDE)
#FLAGS = -lreadline -ltermcap -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

FILES = main.c	init.c	executor.c\
	   	lst_utils.c	cmd_lst_utils.c\
	   	exec_utils.c	utils.c	ft_itoa.c\
	   	ft_atoi.c	ft_split.c	errors.c\
		pwd.c	echo.c	cd.c	unset.c\
		env.c	ft_exit.c	export.c\
		export_empty_args.c	export_utils.c\
		env_vars_utils.c	dup_utils.c\
		redir.c\
		find_cmd.c	free_utils.c	signals.c\
		parser_1.c	parser_2.c	parser_3.c\
		parser_4.c	parser_5.c	parser_6.c\
		parser_7.c	parser_8.c	parser_9.c\
		multiple_pipe.c	exec_cmd.c solocmd.c\

VPATH = srcs/\
		srcs/builtins\

HEADERS = includes/minishell.h\

FILES_O = $(addprefix objs/, $(notdir $(FILES)))
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(FILES_O:.c=.o)
OBJDIR = objs/

NB = $(words $(FILES))
INDEX = 0

objs/%.o : %.c Makefile $(HEADERS)
	@$(CC) $(CFLAGS) -c  $(READCLUDE) $< -o $@ 
	@$(eval PERCENT=$(shell expr $(INDEX) '*' 100 / $(NB)))
	@$(eval PROGRESS=$(shell expr $(INDEX) '*' 30 / $(NB)))
	@printf "\r\033[38;5;87mMAKE MINISHELL %2d%%\033[0m \033[48;5;32m%*s\033[0m %s\033[K" $(PERCENT) $(PROGRESS) "" $(notdir $@)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir objs/

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE)
	@printf "\r\033[38;5;82mMINISHELL DONE\033[0m\033[K\n"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)
	@printf "\033[38;5;85mCLEAN\033[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@printf "\033[38;5;84mFULL CLEAN\033[0m\n"

re: fclean all
