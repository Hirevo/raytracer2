/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Sat Apr  1 04:52:22 2017 Nicolas Polomack
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
  sfVector3f	r;
}		t_ray;

typedef struct	s_light
{
  sfVector3f	pos;
  sfColor	col;
  float		ambient;
}		t_light;

typedef struct		s_obj
{
  char			type;
  sfVector3f		pos;
  sfVector3f		r;
  sfVector2f		p1;
  sfVector2f		p2;
  float			rad;
  float			aper;
  sfColor		col;
  t_my_framebuffer	*buffer;
  float			height;
  float			reflect;
  float			spec_coef;
}			t_obj;

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
  float		focal_dist;
  t_ray		ray;
  t_obj		*from;
  int		depth;
  t_window	*w;
  t_params      *params;
}               t_thread;

typedef struct		s_config
{
  int			stereo;
  int			ssaa;
  int			bmp;
  int			live;
  int			fov;
  float			ambient;
  int			reflect_depth;
  int			depth_rays;
  int			shadow_rays;
}			t_config;

typedef struct		s_params
{
  t_config		config;
  sfVector2i		screen_size;
  sfVector3f		start;
  sfVector3f		r;
  t_light		*lights;
  float			(**intersect)(sfVector3f, sfVector3f, t_obj *);
  void			(**get_normal)(t_thread *, t_obj *);
  void			**libs;
  int			*id;
  int			t_count;
  pthread_mutex_t	mutex;
  pthread_t		*t;
  long int		seed;
  int			progress;
  int			nb_lights;
  int			nb_objs;
  t_obj			*objs;
}			t_params;

typedef struct		s_window
{
  pthread_mutex_t	mutex;
  sfRenderWindow	*window;
  sfRenderWindow        *window2;
  sfTexture		*save_t;
  sfTexture		*texture;
  sfTexture             *texture2;
  sfSprite		*save_s;
  sfSprite		*sprite;
  sfSprite              *sprite2;
  t_my_framebuffer	*save;
  t_my_framebuffer	*buffer;
  t_my_framebuffer      *buffer2;
}			t_window;

/*
** intersect/intersect_sphere.c
*/
float	intersect_sphere(sfVector3f, sfVector3f, t_obj *);

/*
** intersect/intersect_plane.c
*/
float	intersect_plane(sfVector3f, sfVector3f, t_obj *);

/*
** intersect/intersect_cyl.c
*/
float	intersect_cyl(sfVector3f, sfVector3f, t_obj *);
float	intersect_closed_cyl(sfVector3f, sfVector3f, t_obj *);

/*
** intersect/intersect_cone.c
*/
float	intersect_cone(sfVector3f, sfVector3f, t_obj *);
float	intersect_closed_cone(sfVector3f, sfVector3f, t_obj *);

/*
** intersect/intersect_disk.c
*/
float	intersect_disk(sfVector3f, sfVector3f, t_obj *);

/*
** intersect/intersect_limited_plane.c
*/
sfVector3f	create_vet3(float, float, float);
float		intersect_limited_plane(sfVector3f, sfVector3f, t_obj *);

/*
** intersect/intersect_triangle.c
*/
float		norm2(sfVector2f);
sfVector2f	create_vet2(float, float);
float		intersect_triangle(sfVector3f, sfVector3f, t_obj *);

/*
** calc/normals.c
*/
void	get_normal_sphere(t_thread *, t_obj *);
void	get_normal_plane(t_thread *, t_obj *);
void	get_normal_cyl(t_thread *, t_obj *);
void	get_normal_cone(t_thread *, t_obj *);

/*
** calc/calc_dir_vector.c
*/
sfVector3f	calc_dir_vector(sfVector2i, float, float, int);

/*
** calc/focal.c
*/
void	set_focal_dist(t_thread *);

/*
** window.c
*/
void		render_frame(t_thread *);

/*
** raytrace.c
*/
sfVector3f	prepare(sfVector3f, t_obj *, int);
sfVector3f	anti_prepare(sfVector3f, t_obj *, int);
float		gather_dist(t_thread *, int);
void		prepare_raytrace(t_thread *);
sfColor		raytrace(t_thread *);

/*
** thread.c
*/
void	update_frame(t_window *, pthread_mutex_t *, int);
int	init_thread(t_window *, t_params *);

/*
** libs.c
*/
int	load_libs(t_params *);

/*
** lights/light.c
*/
sfColor		calc_lights(t_thread *, t_obj *);
void		prepare_light_calc(t_thread *, t_obj *, float);
sfColor		eval_luminosity(t_thread *, sfColor, float *);
int		is_obstructed(t_thread *, t_obj *);
float		get_light_coef(sfVector3f, sfVector3f);

/*
** calc/colors.c
*/
sfColor		get_shadow_color(t_thread *, t_obj *);
sfColor		average_colors(sfColor *, int);

/*
** bmp/merge.c
*/
t_my_framebuffer	*merge_buffers(int, ...);

/*
** lights/reflect.c
*/
void		prepare_light_ray(t_thread *, int);
sfColor		apply_reflect(sfColor, sfColor, float);
sfColor		light_effects(t_thread *, t_obj *, sfColor);
sfColor		apply_effects(t_thread *, t_obj *, float);

/*
** lights/specular.c
*/
sfColor		specular_effect(sfColor, t_thread *, t_obj *, int);

/*
** stereo/stereoscopy.c
*/
void	render_stereo_frame(t_thread *);

/*
** calc/rotation.c
*/
void	rx(sfVector3f *, float);
void	ry(sfVector3f *, float);
void	rz(sfVector3f *, float);
void	rotation(sfVector3f *, sfVector3f *);
void	anti_rotation(sfVector3f *, sfVector3f *);

/*
** parse/proc.c
*/
int	get_core_count();

/*
** parse/args.c
*/
void	parse_args(t_params *, int, char **);

/*
** alloc.c
*/
void	init_buffers(t_window *, t_params *);
void	save_buffers(t_window *, t_params *);

/*
** rand.c
*/
int		my_rand(long int);
long int	init_seed(int, char **, char **, void *);

/*
** misc/disp_guide.c
*/
int	disp_guide();

#endif /* !RAYTRACER_H_ */
