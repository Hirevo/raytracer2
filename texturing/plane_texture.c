/*
** plane_texture.c for plane in /home/Maxime/delivery/MUL/raytracer2/texturing/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Wed Apr  5 15:40:29 2017 Maxime Jenny
** Last update	Wed Apr 05 16:42:51 2017 Full Name
*/

#include "raytracer.h"

sfColor		plane_texture(t_objs *obj, sfVector3f impact)
{
  sfColor	col;
  int		u;
  int		v;

  u = impact.x - obj->pos.x;
  v = impact.y - obj->pos.y;
  col.r = obj->buffer->pixels[(v * obj->buffer->width + u) * 4];
  col.g = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 1];
  col.b = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 2];
  col.a = obj->buffer->pixels[(v * obj->buffer->width + u) * 4 + 3];
  return (col);
}
