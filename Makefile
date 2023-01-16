NAME = minishell
CC = cc
FLAG = -Wall -Werror -Wextra -fsanitize=undefined -g
READLINE_LINK = -lreadline -L /$(shell brew --prefix readline)/lib
READLINE_COM = -I /$(shell brew --prefix readline)/include
TERMCAP = -lncurses
RM = rm -rf
SRCS = \
		./srcs/main.c\
		./srcs/ft_split.c\
		./srcs/ft_util.c\
		./srcs/tokenize.c\
		./srcs/util.c\
		./srcs/signal.c\
		./srcs/parse.c\
		./srcs/pipeline.c

OBJS = $(SRCS:.c=.o)
HEADER = ./includes/

%.o : %.c
	$(CC) $(FLAG) $(READLINE_COM) -I $(HEADER) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAG) $(READLINE_LINK) $(TERMCAP) -o $(NAME) $(OBJS)

all : $(NAME)

clean :
	$(RM) srcs/*.o

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
