/*
** raytracer.h for raytracer in /home/nicolaspolomack/tests/raytracer
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Sun Feb  5 14:37:35 2017 Nicolas Polomack
** Last update Tue May 23 20:01:17 2017 Nicolas Polomack
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# include <SFML/Graphics.h>
# include <pthread.h>
# include "sfcaster.h"

# define GREY		get_sfcolor(150, 150, 150, 255)
# define SIZE_BUF	2048
# define MATERIAL	"material"
# define LIGHT		"light"
# define OBJ		"obj"
# define CAMERA		"<camera"
# define COLOR		"<color"
# define TEXT		"<texture"
# define POINT		"<point"
# define AMBIENT	"<ambient"
# define OBJ_F		"<obj"
# define POS_N		"pos="
# define FILE_N		"file="
# define ROT_N		"rot="
# define P1_N		"p1="
# define P2_N		"p2="
# define RAD_N		"rad="
# define APER_N		"aperture="
# define HEIGHT_N	"height="
# define REFLECT_N	"reflect="
# define REFRACT_N	"refract="
# define REFR_IDX_N	"refr_index="
# define SPEC_COEF_N	"spec_coef="
# define MAT_N		"material="
# define VAL_N		"val="
# define NAME_N		"name="
# define COLOR_N	"color="
# define TEXT_N		"src="
# define ARGS_STR	"Suh"
# define STEREO		"--stereo"
# define TESLA		"--tesla="
# define DEPTH		"--depth="
# define SSAA		"--ssaa="
# define SOFT		"--soft="
# define RES		"--res="
# define DOF		"--dof="
# define FOV		"--fov="

typedef struct s_window t_window;
typedef struct s_params t_params;

typedef struct	s_obj_file
{
  int		nb_poly;
  int		nb_vert;
  sfVector3f	*p1;
  sfVector3f	*p2;
  sfVector3f	*p3;
}		t_obj_file;

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
}		t_light;

typedef struct		s_material
{
  char			*name;
  int			type;
  char			*path;
  t_my_framebuffer	*buf;
  sfColor		color;
  struct s_material	*next;
}			t_material;

typedef struct		s_l_light
{
  sfVector3f		pos;
  sfColor		col;
  struct s_l_light	*next;
}			t_l_light;

typedef struct	s_p_light
{
  float		ambient;
  t_l_light	*light;
}		t_p_light;

typedef struct		s_p_obj
{
  char			type;
  sfVector3f		pos;
  sfVector3f		rot;
  sfVector2f		p1;
  sfVector2f		p2;
  float			rad;
  float			aper;
  sfColor		col;
  t_obj_file		*obj_parse;
  char			*file;
  t_my_framebuffer	*buffer;
  float			height;
  float			reflect;
  float			refract;
  float			refr_index;
  float			spec_coef;
  struct s_p_obj	*next;
}			t_p_obj;

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
  float			refract;
  float			refr_index;
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
  sfColor	*depth_col;
  sfColor	*ssaa_col;
  float		focal_dist;
  float		refr;
  t_ray		ray;
  t_obj		*from;
  int		idx;
  int		depth;
  int		tesla_lvl;
  int		primary;
  t_window	*w;
  t_params	*params;
  int		id;
}               t_thread;

typedef struct	s_config
{
  int		stereo;
  int		ssaa;
  int		tesla;
  int		bmp;
  int		live;
  int		fov;
  float		ambient;
  int		reflect_depth;
  int		depth_rays;
  int		shadow_rays;
  char		*scene_file;
}		t_config;

typedef struct		s_params
{
  t_config		config;
  sfVector2i		screen_size;
  sfVector3f		start;
  sfVector3f		r;
  t_light		*lights;
  float			(**intersect)(sfVector3f, sfVector3f, t_obj *);
  void			(**get_normal)(t_thread *, t_obj *);
  sfColor		(**apply_tex)(sfVector3f, t_obj *);
  void			**libs;
  int			*id;
  int			t_count;
  pthread_mutex_t	mutex;
  pthread_t		*t;
  long int		seed;
  int			help;
  int			nb_lights;
  int			nb_objs;
  int			tesla_lvl;
  t_obj			*objs;
  t_obj_file		*obj_data;
}			t_params;

typedef struct		s_window
{
  float			progress;
  sfVector2i		sizes;
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
  unsigned long long	time_start;
}			t_window;

/*
** texturing/sphere_texture.c
*/
sfColor	sphere_texture(sfVector3f, sfVector3f, sfVector3f, t_obj *);

/*
** texturing/plane_texture.c
*/
sfColor	plane_texture(sfVector3f, t_obj *);

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
** teslation.c
*/

void	render_frame_tesla(t_thread *);

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
** render.c
*/
void	check_render(t_params *, t_window *);

/*
** event.c
*/
void	check_keys(t_params *);

/*
** libs.c
*/
int	load_libs(t_params *);

/*
** lights/light.c
*/
sfColor		calc_lights(t_thread *, t_obj *, sfColor);
void		prepare_light_calc(t_thread *, t_obj *, float);
sfColor		eval_luminosity(t_thread *, sfColor, float *);
int		is_obstructed(t_thread *, t_obj *);
float		get_light_coef(sfVector3f, sfVector3f);

/*
** calc/colors.c
*/
sfColor		get_shadow_color(t_thread *, sfColor);
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
** lights/refract.c
*/
void	prepare_refract(t_thread *, float, float);

/*
** lights/specular.c
*/
sfColor		specular_effect(sfColor, t_thread *, t_obj *, int);

/*
** lights/shadows.c
*/
sfColor		diffuse_shadows(t_thread *, sfColor, t_obj *, int);

/*
** stereo/stereoscopy.c
*/
void	render_stereo_frame(t_thread *);

/*
** ssaa/ssaa.c
*/
void	render_ssaa(t_thread *);

/*
** depth_of_field/depth.c
*/
sfColor	dof(t_thread *, float, float);

/*
** calc/rotation.c
*/
void	rx(sfVector3f *, float);
void	ry(sfVector3f *, float);
void	rz(sfVector3f *, float);
void	rotation(sfVector3f *, sfVector3f *);
void	anti_rotation(sfVector3f *, sfVector3f *);

/*
** obj/my_getfloat.c
*/

float	my_getfloat(char *);

/*
** obj/my_split_char.c
*/

char	**my_split_char(char *, char);

/*
** obj/parse_obj.c
*/

t_obj_file	*parse_obj_file(char *);

/*
** obj/parse_poly.c
*/

int	get_nb_poly(char **);
int	parse_poly(char **, sfVector3f *, t_obj_file *);

/*
** obj/parse_pos_vert.c
*/

int		tab_len(char **);
int		nb_vert(char **);
sfVector3f	*parse_pos_vert(char **, t_obj_file *);

/*
** parse/get_file.c
*/

char	**get_file(char *);

/*
** parse/parse_from_file.c
*/

int	parse_from_file(t_params *, char *);

/*
** parse/proc.c
*/
int	get_core_count();

/*
** parse/parse_material.c
*/

t_material	*parse_material(char **);

/*
** parse/parse_light.c
*/

t_p_light	*parse_light(char **, t_material *);

/*
** parse/parse_obj.c
*/

t_p_obj		*parse_obj(char **, t_material *);

/*
** parse/add_material.c
*/

int	add_material(t_material **, t_material);

/*
** parse/add_light.c
*/

int	add_light(t_l_light **, t_l_light);

/*
** parse/add_obj.c
*/

int	add_obj(t_p_obj **, t_p_obj);

/*
** parse/get_head_node.c
*/

char	*get_head_node(char **, char *);

/*
** parse/get_text_from_node.c
*/

char	*get_text_from_node(char **, sfVector2i *);

/*
** parse/get_text_from_born.c
*/

char	*get_text_from_born(char **, sfVector2i *);

/*
** parse/get_val_from_node.c
*/

char	*get_val_from_node(char *, char *);

/*
** parse/get_color_from_node.c
*/

sfColor	get_color_from_node(char *, char *);

/*
** parse/get_col_from_mat.c
*/

sfColor		get_col_from_mat(char *, char *, t_material *);

/*
** parse/get_pos_from_node.c
*/

sfVector3f	get_pos_from_node(char *, char *);

/*
** parse/get_pos2_from_node.c
*/

sfVector2f	get_pos2_from_node(char *, char *);

/*
** parse/get_pc_from_node.c
*/

float	get_pc_from_node(char *, char *);

/*
** parse/get_int_from_node.c
*/

float	get_int_from_node(char *, char *);
float	get_pint_from_node(char *, char *);

/*
** parse/search_material.c
*/

t_material	*search_material(char *, t_material *);

/*
** parse/my_epurstr.c
*/

char	*my_epurstr(char *);

/*
** parse/my_getnbr.c
*/

int	getnbr_parse(char *);

/*
** parse/extract_str_from_born.c
*/

char	*extract_str_from_born(char **, sfVector2i);

/*
** parse/set_config.c
*/

void	set_config(t_params *, t_p_light *);

/*
** parse/convert_light.c
*/

int	convert_light(t_params *, t_l_light *);

/*
** parse/convert_obj.c
*/

int	convert_obj(t_params *, t_p_obj *);

/*
** parse/args.c
*/

int	parse_args(t_params *, int, char **);

/*
** parse/set_camera.c
*/

void	set_camera(t_params *, char **);

/*
** time.c
*/

unsigned long long	get_time();
char			*get_time_calc();

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
