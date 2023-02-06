NAME = minishell
CC = cc
FLAG = -Wall -Werror -Wextra
READLINE_LINK = -lreadline -L /$(shell brew --prefix readline)/lib
READLINE_COM = -I /$(shell brew --prefix readline)/include
TERMCAP = -lncurses
RM = rm -rf
SRCS = \
		./srcs/main.c\
		./srcs/shell.c\
		./srcs/redirection_util.c\
		./srcs/ft_split.c\
		./srcs/ft_util.c\
		./srcs/ft_util2.c\
		./srcs/ft_util3.c\
		./srcs/ft_util4.c\
		./srcs/util.c\
		./srcs/util2.c\
		./srcs/util3.c\
		./srcs/signal.c\
		./srcs/parse.c\
		./srcs/syntax.c\
		./srcs/hs_parse_util.c\
		./srcs/pipe.c\
		./srcs/redirection.c\
		./srcs/builtin.c\
		./srcs/pipe_util.c\
		./srcs/builtin/env.c\
		./srcs/builtin/pwd.c\
		./srcs/builtin/export.c\
		./srcs/builtin/unset.c\
		./srcs/builtin/hj_envp_del.c\
		./srcs/builtin/hj_envp_bigtaging.c\
		./srcs/builtin/echo.c\
		./srcs/builtin/cd.c\
		./srcs/builtin/exit.c\
		./srcs/parsing/hj_small_del.c\
		./srcs/parsing/hj_split_change.c\
		./srcs/parsing/hj_split_change2.c\
		./srcs/parsing/hj_split_cmd.c\
		./srcs/parsing/hj_split_util.c\
		./srcs/parsing/hj_split_util2.c\
		./srcs/parsing/hj_split_util3.c\
		./srcs/parsing/hj_split_util4.c\
		./srcs/parsing/hj_split_util5.c

OBJS = $(SRCS:.c=.o)
HEADER = ./includes/

%.o : %.c
	$(CC) $(FLAG) $(READLINE_COM) -I $(HEADER) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAG) $(READLINE_LINK) $(TERMCAP) -o $(NAME) $(OBJS)

all : $(NAME)

clean :
	$(RM) srcs/*.o
	$(RM) srcs/builtin/*.o
	$(RM) srcs/parsing/*.o

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
