/*
** sfraytracer.c for mycsfml in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:33:15 2017 Nicolas Polomack
** Last update Mon Feb 27 20:17:59 2017 Nicolas Polomack
*/

#include <math.h>
#include <SFML/Graphics.h>

float	norm(sfVector3f v1)
{
  return (sqrtf(powf(v1.x,2) + powf(v1.y,2) + powf(v1.z,2)));
}

sfVector3f	normalize(sfVector3f v)
{
  float		n;

  n = norm(v);
  v.x /= n;
  v.y /= n;
  v.z /= n;
  return (v);
}

float	dot(sfVector3f v1, sfVector3f v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

sfColor		average_col(sfColor *col, int nb)
{
  sfColor	final;
  int		rgb[3];
  int		i;

  rgb[0] = 0;
  rgb[1] = 0;
  rgb[2] = 0;
  i = -1;
  while (++i < nb)
    {
      rgb[0] += col[i].r;
      rgb[1] += col[i].g;
      rgb[2] += col[i].b;
    }
  final.r = rgb[0] / nb;
  final.g = rgb[1] / nb;
  final.b = rgb[2] / nb;
  final.a = 255;
  return (final);
}
