/*
** colors.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Tue Mar 28 14:18:43 2017 Nicolas Polomack
** Last update Sun Apr  9 15:08:08 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include "raytracer.h"

sfColor		get_shadow_color(t_thread *t, sfColor col)
{
  float		coef;
  sfColor	ret;

  coef = t->params->config.ambient;
  ret.r = ((float)col.r) * coef;
  ret.g = ((float)col.g) * coef;
  ret.b = ((float)col.b) * coef;
  ret.a = 255;
  return (ret);
}

sfColor		average_colors(sfColor *col, int nb_l)
{
  sfColor	final;
  int		rgb[3];
  int		i;

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
  i = -1;
  while (++i < nb_l)
    {
      rgb[0] += col[i].r;
      rgb[1] += col[i].g;
      rgb[2] += col[i].b;
    }
  final.r = rgb[0] / nb_l;
  final.g = rgb[1] / nb_l;
  final.b = rgb[2] / nb_l;
  final.a = 255;
  return (final);
}
