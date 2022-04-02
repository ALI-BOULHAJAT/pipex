NAME = pipex

SRC = pipex_M/pipex.c pipex_M/error.c pipex_M/rest_func.c
SRC_BONUS = pipex_B/pipex_B.c pipex_B/error_B.c pipex_B/rest_func_B.c pipex_B/get_next_line.c pipex_B/rest_func_B2.c
CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

OBJECT = $(SRC:.c=.o)

OBJECT_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECT)	
	make -C libft/
	gcc  libft/libft.a $(CFLAGS) $(OBJECT) -o $(NAME) 

bonus : $(OBJECT_BONUS)
	rm -rf $(OBJECT) $(NAME)
	make -C libft/
	gcc libft/libft.a $(CFLAGS) $(OBJECT_BONUS) -o $(NAME)
 
clean :
	make fclean -C libft/
	rm -rf $(OBJECT) $(OBJECT_BONUS)

fclean : clean
	rm -rf $(NAME)
	rm -rf outfile
	rm -rf .infile

re : fclean all

.PHONY : all bonus clean fclean re