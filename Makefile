##
## Makefile for Makefile in /home/nicolas/graphical/bootstrap_wireframe/
##
## Made by Nicolas Polomack
## Login   <nicolas.polomack@epitech.eu>
##
## Started on  Tue Nov 15 09:05:43 2016 Nicolas Polomack
## Last update Thu May 25 18:43:03 2017 Cédric THOMAS
##

MAKESO	=	make --no-print-directory -sC libs

MAKE2	=	make --no-print-directory -sC lib/my

MAKESOC	=	make --no-print-directory -sC lib/socket

MAKE1	=	make --no-print-directory -sC lib/mycsfml

SRC	=	calc/colors.c				\
		calc/focal.c				\
		calc/rotation.c				\
		calc/normals.c				\
		calc/calc_dir_vector.c			\
		cluster/client.c			\
		cluster/check_cli_ready.c		\
		cluster/com_sock.c			\
		cluster/get_ip.c			\
		cluster/manag_client.c			\
		cluster/treat_resp_wait.c		\
		cluster/treat_resp_cli.c		\
		cluster/recv_parse.c			\
		cluster/send_parse.c			\
		cluster/server.c			\
		cluster/wait_connection.c		\
		cluster/divide_scene.c			\
		window.c				\
		raytrace.c				\
		thread.c				\
		render.c				\
		libs.c					\
		alloc.c					\
		event.c					\
		rand.c					\
		tesselation.c				\
                get_next_line.c			        \
                lights/light.c		                \
		lights/reflect.c			\
		lights/refract.c			\
		lights/specular.c			\
		lights/shadows.c			\
		stereo/stereoscopy.c			\
		ssaa/ssaa.c				\
		depth_of_field/depth.c			\
		obj/my_getfloat.c			\
		obj/my_split_char.c			\
		obj/parse_obj.c				\
		obj/parse_poly.c			\
		obj/parse_pos_vert.c			\
		obj/render.c				\
		parse/proc.c				\
		parse/args.c				\
		parse/add_obj.c				\
		parse/parse_from_file.c			\
		parse/parse_obj.c			\
		parse/set_camera.c			\
		parse/my_getnbr.c			\
		parse/get_head_node.c			\
		parse/get_text_from_born.c		\
		parse/get_val_from_node.c		\
		parse/get_color_from_node.c		\
		parse/get_color_from_mat.c		\
		parse/get_int_from_node.c		\
		parse/get_pos_from_node.c		\
		parse/get_pos2_from_node.c		\
		parse/get_pc_from_node.c		\
		parse/search_material.c			\
		parse/parse_material.c			\
		parse/extract_str_from_born.c		\
		parse/parse_light.c			\
		parse/convert_light.c			\
		parse/convert_obj.c			\
		parse/add_material.c			\
		parse/add_light.c			\
		parse/my_epurstr.c			\
		parse/set_config.c			\
		parse/get_file.c			\
                texturing/sphere_texture.c		\
		texturing/plane_texture.c		\
		time.c					\
		misc/disp_guide.c			\
                bmp/load_bmp.c                          \
                bmp/merge.c                             \
                bmp/save_bmp.c				\
\
		solver/caster.c				\
		solver/fourth/solus_four_part1.c	\
		solver/fourth/solus_four_part2.c	\
		solver/fourth/solver_four.c		\
		solver/sec/solver_sec.c			\
		solver/solver.c				\
		solver/third/solver_three.c


OBJ	=	$(SRC:.c=.o)

LIBS	=	-lm -Llib/my -lmy -Llib/mycsfml -Llib/socket -lmycsfml-so -lc_graph_prog -lsocket_lib

FLAGS	=	$(LIBS) $(CFLAGS) -ansi -pipe -ldl -Wl,-rpath=$(shell pwd)/lib/mycsfml -rdynamic

CFLAGS	=	-Iinclude -I../include -pthread -O2 -g

REDDARK	=	\033[31;2m

RED	=	\033[31;1m

GREEN	=	\033[32;1m

YEL	=	\033[33;1m

BLUE	=	\033[34;1m

PINK	=	\033[35;1m

CYAN	=	\033[36;1m

RES	=	\033[0m

NAME	=	raytracer2

all:		$(NAME)

$(NAME):	.SILENT

.SILENT:	$(OBJ)
		@echo
		@echo -e "$(GREEN)Everything compiled smoothly. Now compiling dependancies...$(RES)"
		@echo
		@echo -en "$(CYAN)Compiling libmy...$(RES)"
		@$(MAKE1)
		@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
		@echo -en "$(CYAN)Compiling libmycsfml...$(RES)"
		@$(MAKE2)
		@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
		@echo -en "$(CYAN)Compiling socketlib...$(RES)"
		@$(MAKESOC)
		@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
		@echo -en "$(CYAN)Compiling .so files...$(RES)"
		@$(MAKESO)
		@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
		@echo -en "$(CYAN)Linking raytracer2...$(RES)"
		@gcc -o $(NAME) $(OBJ) $(FLAGS)
		@echo -e "\t$(GREEN)OK$(RES)$(CYAN)!$(RES)"
		@echo
		@echo -e "$(GREEN)---- RAYTRACER2 READY ----$(RES)"
		@echo

clean:
		@$(foreach var, $(OBJ), if [ -e $(var) ] ; then \
	        printf "[$(RED)RM$(RES)] $(YEL)$(var)$(RES)\n" \
		&& $(RM) $(var) ; fi ;)
		@$(MAKE1) clean
		@$(MAKE2) clean
		@$(MAKESO) clean
		@$(MAKESOC) clean

fclean:		clean
		@if [ -e $(NAME) ] ; then \
	        printf "[$(RED)RM EXEC$(RES)] $(YEL)$(NAME)$(RES)\n" \
	        && rm -f $(NAME) ; fi
		@$(MAKE1) fclean
		@$(MAKE2) fclean
		@$(MAKESO) fclean
		@$(MAKESOC) fclean

re:	fclean all

%.o:		%.c
		@echo -e "[$(RED)COMPILE$(RES)] $(YEL)$<$(RES) $(BLUE)=>$(RES) $(YEL)$@$(RES)"
		@gcc $(CFLAGS) -o $@ -c $<
