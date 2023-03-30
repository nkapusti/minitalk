NAME_SERVER =	server
NAME_CLIENT =	client
SRC_SERVER =	server.c
SRC_CLIENT =	client.c
lib = libft
libft	= libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(libft) $(NAME_SERVER) $(NAME_CLIENT)

$(libft):
	@make -C $(lib)

$(NAME_SERVER):
	$(CC) $(CFLAGS) $(SRC_SERVER) libft/libft.a -o $(NAME_SERVER)
	
$(NAME_CLIENT):
	$(CC) $(CFLAGS) $(SRC_CLIENT) libft/libft.a -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm $(NAME_SERVER) $(NAME_CLIENT)
	@make clean -C $(lib)

fclean: clean
	@make fclean -C $(lib)
	
re: fclean all

.PHONY: all clean fclean re
