NAME = pipex

SRC = pipex.c error.c rest_func.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

OBJECT = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECT)	
	make -C libft/
	gcc  libft/libft.a $(CFLAGS) $(OBJECT) -o $(NAME) 

clean :
	make fclean -C libft/
	rm -rf $(OBJECT)

fclean : clean
	rm -rf $(NAME)
	rm -rf outfile

re : fclean all

.PHONY : all clean fclean re