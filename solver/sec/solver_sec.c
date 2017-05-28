/*
** solver_sec.c for solver in /home/cedric/Desktop/solver
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 29 15:04:44 2017 
** Last update Sun May 28 12:33:19 2017 Arthur Knoepflin
*/
#include <stdlib.h>
#include <math.h>
#include "solver.h"

t_solus		*solver_sec(float *poly)
{
  float		delta;
  t_solus	*solus;

  if ((solus = init_solus()) == NULL)
    return (NULL);
  delta = ((poly[1] * poly[1]) - (4 * poly[0] * poly[2]));
  if (delta == 0 && poly[0] != 0)
    {
      if (solus_add(solus, -poly[1] / (2 * poly[0])))
	return (NULL);
      return (solus);
    }
  else if (delta > 0 && poly[0] != 0)
    {
      if (solus_add(solus, (-poly[1] - sqrt(delta)) / (2 * poly[0])))
	return (NULL);
      if (solus_add(solus, (-poly[1] + sqrt(delta)) / (2 * poly[0])))
	return (NULL);
      return (solus);
    }
  return (solus);
}

