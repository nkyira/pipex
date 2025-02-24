NAME = pipex

SRC = main.c
OBJ = $(SRC:.c=.o)

CC = gcc -Wall -Wextra -Werror -g
INCLUDE = -I includes -I libft

LIBFT = libft/libft.a

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L libft -lft -o $(NAME)

$(LIBFT) :
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(INLCUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
