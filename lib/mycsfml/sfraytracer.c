/*
** sfraytracer.c for mycsfml in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:33:15 2017 Nicolas Polomack
** Last update Wed Apr  5 15:00:09 2017 Nicolas Polomack
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

sfVector3f	cross(sfVector3f u, sfVector3f v)
{
  sfVector3f	s;

  s.x = u.y * v.z - u.z * v.y;
  s.y = u.z * v.x - u.x * v.z;
  s.z = u.x * v.y - u.y * v.x;
  return (s);
}
