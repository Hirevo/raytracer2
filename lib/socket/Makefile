##
## Makefile for make in /home/Maxime/perso/echat/lib/socket/
##
## Made by Maxime Jenny
## Login   <maxime.jenny@epitech.eu>
##
## Started on  Tue May  2 15:14:34 2017 Maxime Jenny
## Last update Thu May 25 11:17:38 2017 Maxime Jenny
##

SRC	=	protocol.c 			\
  		create_socket.c			\
		set_sockaddr_in.c		\
		count_the_place.c		\
		error.c				\
		../my/my_find_prime_sup.c	\
		../my/my_getnbr.c		\
		../my/my_isneg.c		\
		../my/my_is_prime.c		\
		../my/my_putchar.c		\
		../my/my_put_nbr.c		\
		../my/my_putstr.c		\
		../my/my_revstr.c		\
		../my/my_strcat.c		\
		../my/my_strcmp.c		\
		../my/my_strlen.c		\
		../my/my_strncat.c		\
		../my/my_strncmp.c		\
		../my/my_strstr.c		\
		../my/my_strdup.c		\
		../my/my_strndup.c

OBJ	=	$(SRC:.c=.o)

NAME	=	./libsocket_lib.a

CFLAGS	+=	-I../../include

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
