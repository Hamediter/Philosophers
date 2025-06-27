SRCS = main.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g3 -c $< -o $@

CC = cc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g3 -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all : ${NAME}

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all