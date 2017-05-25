/*
** caster.c for caster in /home/cedric/Desktop/solver
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 29 13:50:16 2017 
** Last update Sat Apr 29 21:54:34 2017 
*/
#include <stdarg.h>
#include <stdlib.h>
#include "solver.h"

t_solus		*init_solus()
{
  t_solus	*my_solus;

  if ((my_solus = malloc(sizeof(t_solus))) == NULL)
    return (NULL);
  my_solus->nb = 0;
  my_solus->solus = NULL;
  return (my_solus);
}

void		del_solus(t_solus *my_solus)
{
  free(my_solus->solus);
  free(my_solus);
}

int		solus_add(t_solus *my_solus, float solus)
{
  float		*new;
  int		i;

  if ((new = malloc(sizeof(float) * (my_solus->nb + 1))) == NULL)
    return (1);
  i = -1;
  while (++i < my_solus->nb)
    new[i] = my_solus->solus[i];
  new[i] = solus;
  free(my_solus->solus);
  my_solus->solus = new;
  my_solus->nb += 1;
  return (0);
}

void		del_polys(t_poly *my_poly)
{
  free(my_poly->poly);
  free(my_poly);
}

t_poly		*create_poly(int size, ...)
{
  va_list	float_list;
  int		i;
  t_poly	*poly;

  if ((poly = malloc(sizeof(t_poly))) == NULL)
    return (NULL);
  if ((poly->poly = malloc(sizeof(float) * size)) == NULL)
    return (NULL);
  poly->nb = size;
  i = -1;
  va_start(float_list, size);
  while (++i < size)
    poly->poly[i] = va_arg(float_list, double);
  va_end(float_list);
  return (poly);
}
