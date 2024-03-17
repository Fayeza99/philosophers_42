NAME		=	philo
SRC			=	main.c utils.c print_utils.c init.c death.c philo_functions.c
CFLAGS		=	-Wall -Wextra -Werror -pthread -g
OBJ_DIR		=	obj
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

$(NAME) : $(OBJ_DIR) $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean:
	$(RM) -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re