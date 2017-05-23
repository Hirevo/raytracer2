/*
** sfcaster.h for mycsfml in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Dec 21 13:52:00 2016 Nicolas Polomack
** Last update Tue May 23 21:54:43 2017 Arthur Knoepflin
*/

#ifndef SFCASTER_H_
# define SFCASTER_H_

# include <SFML/Graphics.h>
# include <SFML/System.h>

# define PI 3.141592653F

# define GREEN get_sfcolor(39, 174, 96, 255)
# define DARK_BLUE get_sfcolor(44, 62, 80, 255)
# define RED get_sfcolor(192, 57, 43, 255)
# define BLUE get_sfcolor(41, 128, 185, 255)

typedef struct	s_my_framebuffer
{
  sfUint8	*pixels;
  int		width;
  int		height;
} 		t_my_framebuffer;

typedef struct	s_raycast
{
  sfVector2f	rayX;
  sfVector2f	rayY;
  char		axis;
  int		wallX;
  int		wallY;
  float		distance;
}		t_raycast;

t_my_framebuffer	*my_framebuffer_create(int, int);
t_my_framebuffer	*assemble_texture(sfTexture **,
					  sfSprite **, int, int);
sfVector3f		*create_vector3f(float, float, float);
sfVector2f		*create_vector2f(float, float);
sfVector2i		*create_vector2i(int, int);
sfVector3f		v3f(float, float, float);
sfVector2f		v2f(float, float);
void			drawSquare(t_my_framebuffer *, sfVector2i *,
				   sfVector2i *, sfColor);
void			put_pixel(t_my_framebuffer *,
				  int, int, sfColor);
void			draw_line(t_my_framebuffer *,
				  sfVector2f *, sfVector2f *,
				  sfColor);
void			clear_pixels(t_my_framebuffer *);
sfColor			get_sfcolor(int, int, int, int);
void			swap_f(float *, float *);
float			cosr(float);
float			sinr(float);
float			tanr(float);
float			dot(sfVector3f, sfVector3f);
sfVector3f		cross(sfVector3f, sfVector3f);
float			norm(sfVector3f);
sfVector3f		normalize(sfVector3f);
sfColor			average_col(sfColor *, int);

#endif /* !SFCASTER_H_ */
