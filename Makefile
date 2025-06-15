CC      = cc
CFLAGS  = -Wall -Werror -Wextra

SERVER  = server
CLIENT  = client

SRV_SRC = server.c
CLI_SRC = client.c

SRV_OBJ = $(SRV_SRC:.c=.o)
CLI_OBJ = $(CLI_SRC:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SRV_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(CLI_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRV_OBJ) $(CLI_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re