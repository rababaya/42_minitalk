NAME = minitalk
CFLAGS = -Wall -Wextra -Werror

UTILS_SRC = utils.c
UTILS_OBJ = $(UTILS_SRC:.c=.o)

CLIENT_SRC = client.c
SERVER_SRC = server.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_BONUS_SRC = client_bonus.c
SERVER_BONUS_SRC = server_bonus.c
CLIENT_BONUS_OBJ = $(CLIENT_BONUS_SRC:.c=.o)
SERVER_BONUS_OBJ = $(SERVER_BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): server client

bonus: server_bonus client_bonus

server: $(SERVER_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) -o server $(SERVER_OBJ) $(UTILS_OBJ)

server_bonus: $(SERVER_BONUS_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) -o server_bonus $(SERVER_BONUS_OBJ) $(UTILS_OBJ)

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o client $(CLIENT_OBJ) $(UTILS_OBJ)

client_bonus: $(CLIENT_BONUS_OBJ)
	$(CC) $(CFLAGS) -o client_bonus $(CLIENT_BONUS_OBJ) $(UTILS_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(UTILS_OBJ) $(SERVER_BONUS_OBJ) $(CLIENT_BONUS_OBJ)

fclean: clean
	rm -f server client server_bonus client_bonus

re: fclean all

.PHONY:	all clean fclean re bonus
