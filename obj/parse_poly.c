/*
** parse_poly.c for parse_poly in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 10 19:13:48 2017 Arthur Knoepflin
** Last update Wed May 10 21:28:59 2017 Arthur Knoepflin
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

static void	add_poly_to_list(t_poly_obj **ret, sfVector3f pos1, sfVector3f pos2, sfVector3f pos3)
{
  t_poly_obj	*new;
  t_poly_obj	*sauv;

  if ((new = malloc(sizeof(t_poly_obj))) == NULL)
    return ;
  new->pos1 = pos1;
  new->pos2 = pos2;
  new->pos3 = pos3;
  new->next = NULL;
  sauv = *ret;
  if (sauv)
    {
      while (sauv && sauv->next)
	sauv = sauv->next;
      sauv->next = new;
    }
  else
    *ret = new;
}

static void	add_poly(char *line, sfVector3f *pos, t_obj_file *ret)
{
  char		**val;

  if ((val = my_split_char(line + 2, ' ')) == NULL)
    return ;
  if (tab_len(val) != 3)
    return ;
  add_poly_to_list(&(ret->poly_list), pos[my_getnbr(val[0]) - 1],
		   pos[my_getnbr(val[1]) - 1], pos[my_getnbr(val[2]) - 1]);
}

int	parse_poly(char **file, sfVector3f *pos, t_obj_file *ret)
{
  int	i;

  i = 0;
  while (file[i])
    {
      if (file[i][0] == 'f')
	add_poly(file[i], pos, ret);
      i += 1;
    }
  return (0);
}
