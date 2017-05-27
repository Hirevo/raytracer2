/*
** parse_poly.c for parse_poly in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 10 19:13:48 2017 Arthur Knoepflin
** Last update Fri May 26 07:37:25 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

int	get_nb_poly(char **file)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (file[i])
    {
      if (file[i][0] == 'f')
	count += 1;
      i += 1;
    }
  return (count);
}

static void	add_poly(char *line, sfVector3f *pos, t_obj_file *ret, int *j)
{
  char		**val;

  while (*line && *line != ' ')
    line += 1;
  while (*line && *line == ' ')
    line += 1;
  if (!line)
    return ;
  if ((val = my_split_char(line, ' ')) == NULL)
    return ;
  if (tab_len(val) != 3)
    return ;
  ret->p1[*j] = pos[my_getnbr(val[0]) - 1];
  ret->p2[*j] = pos[my_getnbr(val[1]) - 1];
  ret->p3[*j] = pos[my_getnbr(val[2]) - 1];
  *j += 1;
}

int	parse_poly(char **file, sfVector3f *pos, t_obj_file *ret)
{
  int	j;
  int	i;

  i = 0;
  j = 0;
  while (file[i])
    {
      if (file[i][0] == 'f')
	add_poly(file[i], pos, ret, &j);
      i += 1;
    }
  return (0);
}
