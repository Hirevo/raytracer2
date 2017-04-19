##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Wed Apr 19 23:06:24 2017 Arthur Knoepflin
##

MAKESO	=	make --no-print-directory -sC libs

MAKE2	=	make --no-print-directory -sC lib/my

MAKE1	=	make --no-print-directory -sC lib/mycsfml

SRC	=	window.c				\
		raytrace.c				\
		thread.c				\
		libs.c					\
		alloc.c					\
		rand.c					\
		scene.c					\
                get_next_line.c			        \
                lights/light.c		                \
		lights/reflect.c			\
		lights/refract.c			\
		lights/specular.c			\
		stereo/stereoscopy.c			\
		ssaa/ssaa.c				\
		depth_of_field/depth.c			\
		parse/proc.c				\
		parse/args.c				\
		parse/add_obj.c				\
		parse/parse_from_file.c			\
		parse/parse_obj.c			\
		parse/my_getnbr.c			\
		parse/get_head_node.c			\
		parse/get_text_from_born.c		\
		parse/get_val_from_node.c		\
		parse/get_color_from_node.c		\
		parse/get_color_from_mat.c		\
		parse/get_int_from_node.c		\
		parse/get_pos_from_node.c		\
		parse/parse_material.c			\
		parse/parse_light.c			\
		parse/add_material.c			\
		parse/add_light.c			\
		parse/my_epurstr.c			\
		parse/get_file.c			\
                calc/colors.c				\
		calc/focal.c				\
                calc/rotation.c				\
                calc/normals.c				\
                calc/calc_dir_vector.c			\
                texturing/sphere_texture.c		\
		texturing/plane_texture.c		\
		misc/disp_guide.c			\
                bmp/load_bmp.c                          \
                bmp/merge.c                             \
                bmp/save_bmp.c

OBJ	=	$(SRC:.c=.o)

LIBS	=	-lm -Llib/my -lmy -Llib/mycsfml -lmycsfml-so -lc_graph_prog

FLAGS	=	$(LIBS) $(CFLAGS) -ansi -pipe -ldl -Wl,-rpath=$(shell pwd)/lib/mycsfml -rdynamic

CFLAGS	=	-Iinclude -I../include -pthread -g

NAME	=	raytracer2

all:	$(NAME)

$(NAME):$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAGS)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all
