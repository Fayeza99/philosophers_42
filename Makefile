NAME		=	philo
SRC			=	main.c utils.c print_utils.c init.c death.c philo_functions.c
CFLAGS		=	-Wall -Wextra -Werror -pthread -g

all : $(NAME)

$(NAME) : 
	cc $(CFLAGS) -o $(NAME) $(SRC)

clean : 
	rm -rf $(NAME)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re