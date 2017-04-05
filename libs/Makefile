##
## Makefile for raytracer2 in /home/nicolaspolomack/graphical/raytracer2/libs
## 
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
## 
## Started on  Fri Mar 31 19:02:25 2017 Nicolas Polomack
## Last update Wed Apr  5 02:55:00 2017 Nicolas Polomack
##

SRC	=	intersect_sphere.c		\
		intersect_plane.c		\
		intersect_limited_plane.c	\
		intersect_cyl.c			\
		intersect_semi_cone.c		\
		intersect_closed_cyl.c		\
		intersect_cone.c		\
		intersect_closed_cone.c		\
		intersect_disk.c		\
		intersect_triangle.c		\
		intersect_cube.c

OBJ	=	${SRC:.c=.o}

NAME	=	${SRC:.c=.so}

CFLAGS	=	-fPIC -I../include

LDFLAGS	+=	-rdynamic

all:		$(NAME)

$(NAME):	$(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

%.so:	%.o
	@gcc -shared -o $@ $< -I../include -L../lib/my -lmy -L../lib/mycsfml -lmycsfml-so -lm -rdynamic
