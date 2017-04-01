##
## Makefile for Makefile in /home/nicolas/libraries/lib_backup
##
## Made by Nicolas POLOMACK
## Login   <nicolas@epitech.eu>
##
## Started on  Tue Nov  1 12:04:24 2016 Nicolas POLOMACK
## Last update Sat Apr  1 05:26:28 2017 Nicolas Polomack
##

SRC	=	sfcaster.c	\
		sfpixel.c	\
		sfcreator.c	\
		sfcolor.c	\
		sfraytracer.c	\
		sftrig.c

SRC2	=	sfassemble.c

OBJ	=	$(SRC:.c=.o)

OBJ2	=	$(SRC2:.c=.o)

NAME	=	libmycsfml.a

NAME2   =	libmycsfml-sa.a

NAME3	=	libmycsfml-so.so

CFLAGS	=	-I../../include -W -Wall -Wextra -pedantic -O3 -pipe -fPIC

all:	$(NAME)

$(NAME):$(OBJ) $(OBJ2)
	@gcc -o $(NAME3) $(OBJ2) $(OBJ) -shared $(CFLAGS)
	@ar rc $(NAME) $(OBJ) $(OBJ2)
	@ar rc $(NAME2) $(OBJ)

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ2)

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(NAME2)
	@rm -f $(NAME3)

re:	fclean all
