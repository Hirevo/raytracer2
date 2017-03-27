##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Mon Mar 27 03:23:54 2017 Nicolas Polomack
##

MAKE2	=	make --no-print-directory -C lib/my

MAKE1	=	make --no-print-directory -C lib/mycsfml

SRC	=	window.c			\
		raytrace.c			\
		light.c				\
		rotation.c			\
		calc_dir_vector.c		\
		get_next_line.c			\
		normals.c			\
		intersect/intersect_plane.c	\
		intersect/intersect_cyl.c	\
		intersect/intersect_cone.c	\
		intersect/intersect_sphere.c	\
		intersect/intersect_disk.c	\
		bmp/load_bmp.c			\
		bmp/save_bmp.c

OBJ	=	$(SRC:.c=.o)

FLAGS	=	-lm -Llib/my -lmy -Llib/mycsfml -lmycsfml -lc_graph_prog $(CFLAGS) -ansi

CFLAGS	=	-Iinclude -I../include -W -Wall -Wextra -pthread -O3

NAME	=	raytracer2

all:	$(NAME)

$(NAME):$(OBJ)
	@$(MAKE1)
	@$(MAKE2)
	gcc -o $(NAME) $(OBJ) $(FLAGS)

clean:
	rm -f $(OBJ)
	@$(MAKE1) clean
	@$(MAKE2) clean

fclean:	clean
	rm -f $(NAME)
	@$(MAKE1) fclean
	@$(MAKE2) fclean

re:	fclean all
