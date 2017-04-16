/*
** get_text_from_born.c for get_text_fb in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 14 16:26:37 2017 
** Last update Fri Apr 14 17:31:58 2017 
*/

#include <stdlib.h>
#include "raytracer.h"

static int	get_len(char **file, sfVector2i *born)
{
  int		ret;
  sfVector2i	p;

  ret = 0;
  p = born[0];
  while (p.y < born[1].y)
    {
      if (p.y != born[0].y)
	p.x = 0;
      while (file[p.y][p.x] || (p.y == born[1].y && p.x < born[1].x))
	{
	  if (file[p.y][p.x] != '\v' && file[p.y][p.x] != '\t')
	    ret += 1;
	  p.x += 1;
	}
      ret += 1;
      p.y += 1;
    }
  return (ret);
}

static void	assign_text(char **file, sfVector2i *born, char *ret)
{
  int		i;
  sfVector2i	p;

  p = born[0];
  i = 0;
  while (p.y < born[1].y)
    {
      if (p.y != born[0].y)
	p.x = 0;
      while (file[p.y][p.x] || (p.y == born[1].y && p.x < born[1].x))
	{
	  if (file[p.y][p.x] != '\v' && file[p.y][p.x] != '\t')
	    {
	      ret[i] = file[p.y][p.x];
	      i += 1;
	    }
	  p.x += 1;
	}
      ret[i] = ' ';
      i += 1;
      p.y += 1;
    }
}

char	*get_text_from_born(char **file, sfVector2i *born)
{
  int	len;
  char	*epur;
  char	*ret;

  len = get_len(file, born);
  if ((ret = malloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  ret[len] = '\0';
  assign_text(file, born, ret);
  epur = my_epurstr(ret);
  free(ret);
  return (epur);
}
