/*
** sftrig.c for mycsfml in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Dec 23 15:12:35 2016 Nicolas Polomack
** Last update Wed Apr  5 19:32:55 2017 Nicolas Polomack
*/

#include <math.h>
#include "sfcaster.h"

void	swap_f(float *f1, float *f2)
{
  float	temp;

  temp = *f1;
  *f1 = *f2;
  *f2 = temp;
}

float	cosr(float angle)
{
  return (cosf(angle * M_PI / 180.0F));
}

float	sinr(float angle)
{
  return (sinf(angle * M_PI / 180.0F));
}

float	tanr(float angle)
{
  return (tanf(angle * M_PI / 180.0F));
}
