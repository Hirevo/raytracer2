##
## Makefile for Makefile in /home/nicolas/libraries/lib_backup
##
## Made by Nicolas POLOMACK
## Login   <nicolas@epitech.eu>
##
## Started on  Tue Nov  1 12:04:24 2016 Nicolas POLOMACK
## Last update Mon Mar 27 03:22:08 2017 Nicolas Polomack
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

CFLAGS	=	-I../../include -W -Wall -Wextra -pedantic -O3

all:	$(NAME)

$(NAME):$(OBJ) $(OBJ2)
	@ar rc $(NAME) $(OBJ) $(OBJ2)
	@ar rc $(NAME2) $(OBJ)

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ2)

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(NAME2)

re:	fclean all
