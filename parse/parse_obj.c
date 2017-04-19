/*
** parse_obj.c for parse_obj in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Apr 18 21:25:05 2017 Arthur Knoepflin
** Last update Wed Apr 19 23:19:40 2017 Arthur Knoepflin
*/

#include "raytracer.h"
#include "my.h"

static t_p_obj	init_obj_add(void)
{
  t_p_obj	ret;

  my_mset(&ret, 0, sizeof(ret));
  ret.rad = 1;
  ret.aper = 1;
  return (ret);
}

void		parse_obj_elem(char *obj, t_material *mat, t_p_obj **ret)
{
  t_p_obj	add;
  int		i;

  add = init_obj_add();
  add.type = my_getnbr(obj + 1);
  i = 0;
  while (obj[i] && my_strncmp(obj + i, "/>", 2))
    {
      if (!my_strncmp(obj + i, POS_N, my_strlen(POS_N)))
	add.pos = get_pos_from_node(obj + i, POS_N);
      if (!my_strncmp(obj + i, ROT_N, my_strlen(ROT_N)))
	add.rot = get_pos_from_node(obj + i, ROT_N);
      if (!my_strncmp(obj + i, P1_N, my_strlen(P1_N)))
	add.p1 = get_pos_from_node(obj + i, P1_N);
      if (!my_strncmp(obj + i, P2_N, my_strlen(P2_N)))
	add.p2 = get_pos_from_node(obj + i, P2_N);
      if (!my_strncmp(obj + i, RAD_N, my_strlen(RAD_N)))
	add.rad = get_int_from_node(obj + i, RAD_N);
      if (!my_strncmp(obj + i, APER_N, my_strlen(APER_N)))
	add.aper = get_int_from_node(obj + i, APER_N);
      if (!my_strncmp(obj + i, HEIGHT_N, my_strlen(HEIGHT_N)))
	add.height = get_int_from_node(obj + i, HEIGHT_N);
      i += 1;
    }
  add_obj(ret, add);
}

t_p_obj		*parse_obj(char **file, t_material *mat)
{
  int		i;
  int		quote;
  char		*obj;
  t_p_obj	*ret;

  ret = NULL;
  quote = 0;
  i = 0;
  if ((obj = get_head_node(file, OBJ)) == NULL)
    return (NULL);
  while (obj[i])
    {
      if (obj[i] == '"')
	quote = !quote;
      if (!quote && obj[i] == '<')
	parse_obj_elem(obj + i, mat, &ret);
      i += 1;
    }
  return (ret);
}
