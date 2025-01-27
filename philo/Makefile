CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c parse_args.c pthread.c philosopher.c \
		monitoring.c utils.c

OBJS_DIR = objs
OBJS = $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

HEADERS = -I.

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c philo.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
