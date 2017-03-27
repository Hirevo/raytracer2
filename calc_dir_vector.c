/*
** calc_dir_vector.c for bootstrap raytracer1 in /home/nicolaspolomack/tests/raytracer_test
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb  6 23:29:14 2017 Nicolas Polomack
** Last update Sun Feb 26 03:45:40 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>
#include "sfcaster.h"

sfVector3f	calc_dir_vector(sfVector2i screen_size,
				float x, float y, int fov)
{
  sfVector3f	dir;

  dir.x = (screen_size.x / 2) / tanr(fov / 2);
  dir.y = ((float)(screen_size.x / 2)) - ((float)x);
  dir.z = ((float)(screen_size.y / 2)) - ((float)y);
  return (dir);
}
