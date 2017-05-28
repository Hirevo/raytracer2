##
## Makefile for raytracer2 in /home/nicolaspolomack/graphical/raytracer2/libs
## 
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
## 
## Started on  Fri Mar 31 19:02:25 2017 Nicolas Polomack
## Last update Sun May 28 18:17:10 2017 Nicolas Polomack
##

SRC		=	intersect_sphere.c		\
			intersect_plane.c		\
			intersect_limited_plane.c	\
			intersect_cubet.c		\
			intersect_ellipsoid.c		\
			intersect_paraboloid.c		\
			intersect_cyl.c			\
			intersect_semi_cone.c		\
			intersect_closed_cyl.c		\
			intersect_cone.c		\
			intersect_closed_cone.c		\
			intersect_disk.c		\
			intersect_triangle.c		\
			intersect_torus.c

SRC_CUBE	=	intersect_cube.c		\
			get_normal_cube.c

OBJ		=	${SRC:.c=.o}

OBJ_CUBE	=	${SRC_CUBE:.c=.o}

NAME		=	${SRC:.c=.so}

NAME_CUBE	=	intersect_cube.so

CFLAGS		=	-fPIC -I../include -O2

LDFLAGS		+=	-rdynamic

all:		$(NAME) $(NAME_CUBE)

$(NAME):	$(OBJ)

$(NAME_CUBE):	$(OBJ_CUBE)
		gcc -shared -o $(NAME_CUBE) $(OBJ_CUBE) -I../include -L../lib/my -lmy -L../lib/mycsfml -lmycsfml-so -lm -rdynamic -fPIC

clean:
		rm -f $(OBJ) $(OBJ_CUBE)

fclean:		clean
		rm -f $(NAME) $(NAME_CUBE)

re:		fclean all

%.so:	%.o
	@gcc -shared -o $@ $< -I../include -L../lib/my -lmy -L../lib/mycsfml -lmycsfml-so -lm -rdynamic -fPIC
