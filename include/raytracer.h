/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Wed Mar 29 01:44:31 2017 Nicolas Polomack
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# include <SFML/Graphics.h>
# include <pthread.h>
# include "sfcaster.h"

# define GREY get_sfcolor(150, 150, 150, 255)

typedef struct s_window t_window;
typedef struct s_params t_params;

typedef struct	s_ray
{
  sfVector3f	orig;
  sfVector3f	dir;
  float		rx;
  float		ry;
  float		rz;
}		t_ray;

typedef struct	s_light
{
  sfVector3f	pos;
  sfColor	col;
  float		ambient;
}		t_light;

typedef struct	s_obj
{
  char		type;
  sfVector3f	pos;
  float		rx;
  float		ry;
  float		rz;
  float		rad;
  float		aper;
  sfColor	col;
  float		height;
  float		reflect;
  float		spec_coef;
}		t_obj;

typedef struct s_thread
{
  sfVector2i	screen_pos;
  sfVector3f	normal;
  sfVector3f	dir;
  sfVector3f	impact;
  sfVector3f	start;
  sfVector3f	recur_start;
  sfVector2i	offs;
  sfVector2i	end;
  t_ray		ray;
  t_obj		*from;
  int		depth;
  t_window	*w;
  t_params      *params;
}               t_thread;

typedef struct		s_params
{
  sfVector2i		screen_size;
  sfVector3f		start;
  t_light		*lights;
  float			(*intersect[7])(sfVector3f, sfVector3f, t_obj *);
  void			(*get_normal[7])(t_thread *, t_obj *);
  int			t_count;
  pthread_mutex_t	mutex;
  pthread_t		*t;
  int			ssaa;
  int			bmp;
  int			live;
  int			shadow_rays;
  int			depth_rays;
  long int		seed;
  int			progress;
  int			reflect_depth;
  int			nb_lights;
  int			nb_objs;
  t_obj			*objs;
  float			ambient;
  int			fov;
}			t_params;

typedef struct		s_window
{
  pthread_mutex_t	mutex;
  sfRenderWindow	*window;
  sfTexture		*save_t;
  sfTexture		*texture;
  sfSprite		*save_s;
  sfSprite		*sprite;
  t_my_framebuffer	*save;
  t_my_framebuffer	*buffer;
}			t_window;

typedef struct		s_menu
{
  sfRenderWindow	*window;
  sfSprite		*backg_s;
  sfTexture		*backg_t;
  sfSprite		*menu_s;
  sfTexture		*menu_t;
  sfSprite		*option_s;
  sfTexture		*option_t;
  t_my_framebuffer	*backg;
  t_my_framebuffer	*menu;
  t_my_framebuffer	*option;
  int			menu_id;
}			t_menu;

/*
** intersect_sphere.c
*/
float	intersect_sphere(sfVector3f, sfVector3f, t_obj *);

/*
** intersect_plane.c
*/
float	intersect_plane(sfVector3f, sfVector3f, t_obj *);

/*
** intersect_cyl.c
*/
float	intersect_cyl(sfVector3f, sfVector3f, t_obj *);
float	intersect_closed_cyl(sfVector3f, sfVector3f, t_obj *, float);

/*
** intersect_cone.c
*/
float	intersect_cone(sfVector3f, sfVector3f, t_obj *);
float	intersect_closed_cone(sfVector3f, sfVector3f, t_obj *, float);

/*
** intersect_disk.c
*/
float	intersect_disk(sfVector3f, sfVector3f, t_obj *);

/*
** normals.c
*/
void	get_normal_sphere(t_thread *, t_obj *);
void	get_normal_plane(t_thread *, t_obj *);
void	get_normal_cyl(t_thread *, t_obj *);
void	get_normal_cone(t_thread *, t_obj *);

/*
** calc_dir_vector.c
*/
sfVector3f	calc_dir_vector(sfVector2i, float, float, int);

/*
** window.c
*/
void		render_frame(t_thread *);

/*
** raytrace.c
*/
void		prepare_light_calc(t_thread *, t_obj *, float);
float		gather_dist(t_thread *, int);
sfColor		raytrace(t_thread *);

/*
** thread.c
*/
void	update_frame(t_window *, pthread_mutex_t *);
int	init_thread(t_window *, t_params *);

/*
** light.c
*/
sfColor		calc_lights(t_thread *, t_obj *);
sfColor		get_shadow_color(t_thread *, t_obj *);
sfColor		eval_luminosity(t_thread *, sfColor, float *);
int		is_obstructed(t_thread *, t_obj *);
float		get_light_coef(sfVector3f, sfVector3f);

/*
** colors.c
*/
sfColor		average_colors(sfColor *, int);

/*
** reflect.c
*/
void		prepare_light_ray(t_thread *, int);
sfColor		apply_reflect(sfColor, sfColor, float);
sfColor		light_effects(t_thread *, t_obj *, sfColor);
sfColor		apply_effects(t_thread *, t_obj *, float);

/*
** specular.c
*/
sfColor		specular_effect(sfColor, t_thread *, t_obj *, int);

/*
** rotation.c
*/
void	rotation(sfVector3f *, t_obj *);
void	anti_rotation(sfVector3f *, t_obj *);

/*
** parse/proc.c
*/
int	get_core_count();

#endif /* !RAYTRACER_H_ */
