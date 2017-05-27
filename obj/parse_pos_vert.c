/*
** parse_pos_vert.c for parse_pos_vert_obj in /home/arthur/delivery/MUL/raytracer2
**
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
**
** Started on  Tue May  9 22:36:16 2017 Arthur Knoepflin
** Last update Sat May 27 14:16:55 2017 Cédric THOMAS
*/

#include <stdlib.h>
#include "raytracer.h"

int	tab_len(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    i += 1;
  return (i);
}

int	nb_vert(char **file)
{
  int	count;
  int	i;

  i = 0;
  count = 0;
  while (file[i])
    {
      if (file[i][0] == 'v')
	count += 1;
      i += 1;
    }
  return (count);
}

static int	add_pos_ret(sfVector3f *ret, int j, char *line)
{
  char		**sep;

  if ((sep = my_split_char(line + 2, ' ')) == NULL)
    return (1);
  if (tab_len(sep) != 3)
    return (1);
  ret[j].x = atof(sep[0]);
  ret[j].y = atof(sep[1]);
  ret[j].z = atof(sep[2]);
  return (0);
}

sfVector3f	*parse_pos_vert(char **file, t_obj_file *obj)
{
  int		j;
  int		i;
  sfVector3f	*ret;

  if ((ret = malloc(sizeof(sfVector3f) *
		    (obj->nb_vert + 1))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  while (file[i])
    {
      if (file[i][0] == 'v')
	{
	  if (!add_pos_ret(ret, j, file[i]))
	    j += 1;
	}
      i += 1;
    }
  return (ret);
}
