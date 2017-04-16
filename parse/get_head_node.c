/*
** get_head_node.c for get_head_node in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 14 15:15:15 2017 
** Last update Sat Apr 15 13:34:45 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static void	cpy_str(char *ret, char *in)
{
  int		i;

  i = -1;
  while (in[++i])
    ret[i] = in[i];
}

static char	*get_born_name(char *name, int mode)
{
  char		*ret;

  if ((ret = malloc(sizeof(char) *
		    (my_strlen(name) + ((mode == 0) ? 3 : 4)))) == NULL)
    return (NULL);
  ret[my_strlen(name) + ((mode == 0) ? 2 : 3)] = '\0';
  if (mode == 0)
    {
      ret[0] = '<';
      ret[my_strlen(name) + 1] = '>';
    }
  if (mode == 1)
    {
      ret[0] = '<';
      ret[1] = '/';
      ret[my_strlen(name) + 2] = '>';
    }
  cpy_str(ret + ((mode == 0) ? 1 : 2), name);
  return (ret);
}

static sfVector2i	*init_born(void)
{
  sfVector2i		*ret;

  if ((ret = malloc(sizeof(sfVector2i) * 2)) == NULL)
    return (NULL);
  ret[0].x = -1;
  ret[0].y = -1;
  ret[1].x = -1;
  ret[1].y = -1;
  return (ret);
}

static sfVector2i	*get_born(char **file, char **name)
{
  sfVector2i		p;
  int			k;
  int			quote;
  sfVector2i		*ret;

  if ((ret = init_born()) == NULL)
    return (NULL);
  p.y = -1;
  quote = 0;
  while (file[++p.y])
    {
      p.x = -1;
      while (file[p.y][++p.x])
      	{
	  quote = (file[p.y][p.x] == '"') ? !quote : quote;
	  k = -1;
	  while (++k < 2)
	    {
	      if (quote == 0 && !my_strncmp(file[p.y] + p.x,
					    name[k], my_strlen(name[k])))
		ret[k] = p;
	    }
      	}
    }
  return (ret);
}

char		*get_head_node(char **file, char *name)
{
  char		*ret;
  char		*n_born[2];
  sfVector2i	*born;

  n_born[0] = get_born_name(name, 0);
  n_born[1] = get_born_name(name, 1);
  if ((born = get_born(file, n_born)) == NULL)
    return (NULL);
  if (born[0].x == -1 || born[0].y == -1 ||
      born[1].x == -1 || born[1].y == -1)
    return (NULL);
  born[0].x += my_strlen(n_born[0]);
  ret = get_text_from_born(file, born);
  return (ret);
}
