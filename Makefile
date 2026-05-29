NAME = codexion

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

SRC = codexion.c \
parsing.c \
simulation.c \
time.c \
logging.c \
routine.c \
threads.c \
monitor.c \
simulation_utils.c \
dongles.c \
compile_utils.c \
heap.c \
heap_utils.c \
scheduler.c \
parse_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re