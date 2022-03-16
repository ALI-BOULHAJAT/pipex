NAME = pipex

#SRC = 

CC = gcc

CFLAGS = -I.

#OBJECT = $(SRC:.c=.o)

all :
	make -C libft/
	gcc pipex.c libft/libft.a $(CFLAGS) -o $(NAME) 

	

clean :
	make fclean -C libft/

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re