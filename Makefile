NAME = pipex

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(wildcard $(SRC_DIR)*.c)
OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = gcc -Wall -Wextra -Werror -g
INCLUDE = -I includes -I libft

LIBFT = libft/libft.a

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L libft -lft -o $(NAME)

$(LIBFT) :
	$(MAKE) -C libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(INLCUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft fclean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
