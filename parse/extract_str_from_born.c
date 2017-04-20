/*
** extract_str_from_born.c for extract_str_from_born in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 20 23:40:09 2017 Arthur Knoepflin
** Last update Fri Apr 21 00:03:34 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static int	get_len(char **file, sfVector2i born)
{
  int		ret;
  int		i;
  int		j;

  j = -1;
  ret = 0;
  i = born.y;
  while (file[i])
    {
      if (j == -1)
	j = born.x;
      else
	j = 0;
      while (file[i][j])
	{
	  ret += 1;
	  if (!my_strncmp(file[i] + j, "/>", 2))
	    return (ret);
	  j += 1;
	}
      i += 1;
    }
  return (-1);
}

static void	apply(char *ret, char **file, sfVector2i born)
{
  int		idx;
  int		i;
  int		j;

  idx = 0;
  j = -1;
  i = born.y;
  while (file[i])
    {
      j = ((j == -1) ? born.x : 0);
      while (file[i][j])
	{
	  if (file[i][j] == '\v' || file[i][j] == '\t')
	    ret[idx] = ' ';
	  else
	    ret[idx] = file[i][j];
	  idx += 1;
	  if (!my_strncmp(file[i] + j, "/>", 2))
	    return ;
	  j += 1;
	}
      i += 1;
    }
}

char	*extract_str_from_born(char **file, sfVector2i born)
{
  char	*ret;

  if ((ret = malloc(sizeof(char) * (get_len(file, born) + 1))) == NULL)
    return (NULL);
  ret[get_len(file, born)] = '\0';
  apply(ret, file, born);
  return (ret);
}
