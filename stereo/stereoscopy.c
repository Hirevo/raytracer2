/*
** stereoscopy.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Mar 29 19:28:58 2017 Nicolas Polomack
** Last update Sat Apr 22 19:13:54 2017 Nicolas Polomack
*/

#include <math.h>
#include "raytracer.h"

float		prepare_cameras(t_thread *t, sfVector3f cameras[2])
{
  float		distX;
  float		spread;
  float		angle;

  distX = t->focal_dist;
  spread = 5;
  angle = atanf(distX / (2 * distX));
  cameras[0] = t->start;
  cameras[0].y += (spread / 2);
  cameras[1] = t->start;
  cameras[1].y -= (spread / 2);
  return (angle);
}

void		render_red_side(t_thread *t, sfVector3f cameras[2], float angle)
{
  sfColor       col;

  t->screen_pos.x = t->offs.x - 1;
  while (++t->screen_pos.x < t->end.x)
    {
      t->screen_pos.y = t->offs.y - 1;
      while (++t->screen_pos.y < t->end.y)
        {
          t->ray.orig = cameras[0];
          prepare_raytrace(t);
          rz(&t->ray.dir, -angle);
          col = raytrace(t);
          col.g = 0;
          col.b = 0;
          put_pixel(t->w->buffer, t->screen_pos.x, t->screen_pos.y,
                    col);
	}
    }
}

void		render_teal_side(t_thread *t, sfVector3f cameras[2], float angle)
{
  sfColor	col;

  t->screen_pos.x = t->offs.x - 1;
  while (++t->screen_pos.x < t->end.x)
    {
      t->screen_pos.y = t->offs.y - 1;
      while (++t->screen_pos.y < t->end.y)
        {
          t->ray.orig = cameras[1];
          prepare_raytrace(t);
          rz(&t->ray.dir, angle);
          col = raytrace(t);
          col.r = 0;
	  //col.g = 0;
          put_pixel(t->w->buffer2, t->screen_pos.x, t->screen_pos.y,
                    col);
        }
    }
}

void		render_stereo_frame(t_thread *t)
{
  sfVector3f	cameras[2];
  float		angle;

  angle = prepare_cameras(t, cameras);
  render_red_side(t, cameras, angle);
  render_teal_side(t, cameras, angle);
}
