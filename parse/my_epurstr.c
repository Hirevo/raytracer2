/*
** my_epurstr.c for epur_str in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 14 17:00:38 2017 
** Last update Fri Apr 14 17:32:16 2017 
*/

#include <stdlib.h>
#include "raytracer.h"

static int	get_len(char *src)
{
  int		ret;
  int		i;

  i = 0;
  ret = 0;
  while (src[i] && src[i] == ' ')
    i += 1;
  while (src[i])
    {
      if (src[i] != ' ')
	ret += 1;
      else
	{
	  while (src[i + 1] && src[i + 1] == ' ')
	    i += 1;
	  if (src[i + 1])
	    ret += 1;
	}
      i += 1;
    }
  return (ret);
}

static void	assign_val(char *src, char *dst)
{
  int		j;
  int		i;

  i = 0;
  j = -1;
  while (src[i] && src[i] == ' ')
    i += 1;
  while (src[i])
    {
      if (src[i] != ' ')
	dst[++j] = src[i];
      else
	{
	  while (src[i + 1] && src[i + 1] == ' ')
	    i += 1;
	  if (src[i + 1])
	    dst[++j] = ' ';
	}
      i += 1;
    }
}

char	*my_epurstr(char *src)
{
  char	*ret;
  int	len;

  if (!src)
    return (NULL);
  len = get_len(src);
  if ((ret = malloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  ret[len] = '\0';
  assign_val(src, ret);
  return (ret);
}
