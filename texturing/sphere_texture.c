/*
** sphere_texture.c for sphere in /home/Maxime/delivery/MUL/raytracer2/texturing/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu Mar 30 21:46:06 2017 Maxime Jenny
** Last update Thu May 25 23:20:50 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "sfcaster.h"
#include "raytracer.h"

sfColor		sphere_texture(sfVector3f ve, sfVector3f vp, sfVector3f vn,
			       t_obj *obj)
{
  float		phi;
  float		theta;
  int		u;
  int		v;
  sfColor	col;

  phi = acos(-1 * dot(vn, vp));
  theta = (acos(dot(vp, ve) / sin(phi))) / (2 * M_PI);
  v = phi * obj->buffer->height / M_PI;
  if (dot(cross(vn, ve), vp) > 0)
    u = theta * obj->buffer->width;
  else
    u = (1 - theta) * obj->buffer->width;
  col.r = obj->buffer->pixels[(v * obj->buffer->width + u) * 4];
  col.g = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 1];
  col.b = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 2];
  col.a = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 3];
  return (col);
}
