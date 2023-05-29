CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = server.c client.c server_bonus.c client_bonus.c
OBJS = $(SRCS:.c=.o)

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

FT_PRINTF_PATH = ft_printf
FT_PRINTF = $(FT_PRINTF_PATH)/libftprintf.a

YELLOW = \033[0;33m
NC = \033[0m

.PHONY: all clean fclean re

all: server client server_bonus client_bonus

server: server.o $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ server.o -L$(LIBFT_PATH) -lft -L$(FT_PRINTF_PATH) -lftprintf
	@echo "$(YELLOW)      \\                   /"
	@echo "       \\_               _/"
	@echo "         \\  ___/\\  ___/"
	@echo "           \\/   \\/"
	@echo "          _/    /_"
	@echo "         /      \\"
	@echo "        |       |"
	@echo "        |       |"
	@echo "        |       |"
	@echo "         \\     /"
	@echo "          \\   /"
	@echo "           \\_/"
	@echo "           (  )"
	@echo "           |  |"
	@echo "           |  |"
	@echo "           |__|"
	@echo "           /  \\"
	@echo "          /    \\"
	@echo "         /      \\"
	@echo "        /________\\"
	@echo "       /__________\\"
	@echo "      /____________\\"
	@echo "     /______________\\"
	@echo "    /________________\\"
	@echo "   /__________________\\"
	@echo "  /____________________\\"
	@echo " /______________________\\"
	@echo "$(YELLOW)             Dragon animation!$(NC)"

client: client.o $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ client.o -L$(LIBFT_PATH) -lft -L$(FT_PRINTF_PATH) -lftprintf

server_bonus: server_bonus.o $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ server_bonus.o -L$(LIBFT_PATH) -lft -L$(FT_PRINTF_PATH) -lftprintf

client_bonus: client_bonus.o $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $@ client_bonus.o -L$(LIBFT_PATH) -lft -L$(FT_PRINTF_PATH) -lftprintf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(FT_PRINTF):
	make -C $(FT_PRINTF_PATH)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean
	make -C $(FT_PRINTF_PATH) clean

fclean: clean
	rm -f server client server_bonus client_bonus
	rm -f $(LIBFT_PATH)/libft.a $(FT_PRINTF_PATH)/libftprintf.a

re: fclean all
