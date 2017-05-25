/*
** solver.c for solver in /home/cedric/Desktop/solver
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 29 14:30:20 2017 
** Last update Thu May 25 18:36:52 2017 Cédric THOMAS
*/
#include <stdlib.h>
#include <math.h>
#include "solver.h"

t_solus		*solver(t_poly *poly)
{
  t_solus	*solus;
  int		deg;
  int		start;

  start = 0;
  if (poly == NULL || poly->nb < 3 || poly->nb > 5)
    return (NULL);
  while (start < poly->nb && poly->poly[start] == 0)
    start += 1;
  deg = poly->nb - start - 1;
  if (deg == 2)
    solus = solver_sec(poly->poly + start);
  else if (deg == 3)
    solus = solver_three(poly->poly + start);
  else if (deg == 4)
    solus = solver_four(poly->poly + start);
  else
    return (NULL);
  return (solus);
}

float		get_min_pos_solus(t_solus *solus)
{
  int		i;
  float		min;

  i = -1;
  min = -1;
  if (solus == NULL || solus->nb == 0)
    return (-1);
  while (++i < solus->nb)
    {
      if ((min < 0 || (min > 0 && solus->solus[i] < min))
	  && solus->solus[i] > 0)
	min = solus->solus[i];
    }
  return (min);
}

