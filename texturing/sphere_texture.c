/*
** sphere_texture.c for sphere in /home/Maxime/delivery/MUL/raytracer2/texturing/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu Mar 30 21:46:06 2017 Maxime Jenny
** Last update Wed Apr  5 00:37:35 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "sfcaster.h"
#include "raytracer.h"

sfVector3f	cross(sfVector3f u, sfVector3f v)
{
  sfVector3f	s;

  s.x = u.y * v.z - u.z * v.y;
  s.y = u.z * v.x - u.x * v.z;
  s.z = u.x * v.y - u.y * v.x;
  return (s);
}

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
