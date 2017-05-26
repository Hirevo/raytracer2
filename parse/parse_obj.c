/*
** parse_obj.c for parse_obj in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Apr 18 21:25:05 2017 Arthur Knoepflin
** Last update Fri May 26 04:46:43 2017 Nicolas Polomack
*/

#include "raytracer.h"
#include "my.h"

static t_p_obj	init_obj_add(void)
{
  t_p_obj	ret;

  my_mset(&ret, 0, sizeof(ret));
  ret.rad = 1;
  ret.aper = 1;
  ret.refr_index = 1;
  ret.scale = 1;
  ret.spec_coef = 99999999;
  ret.col.r = 255;
  ret.col.g = 255;
  ret.col.b = 255;
  ret.col.a = 255;
  return (ret);
}

static void	core_parse_obj(char *obj, int i, t_p_obj *add)
{
  if (!my_strncmp(obj + i, RAD_N, my_strlen(RAD_N)))
    add->rad = get_int_from_node(obj + i, RAD_N);
  if (!my_strncmp(obj + i, APER_N, my_strlen(APER_N)))
    add->aper = get_int_from_node(obj + i, APER_N);
  if (!my_strncmp(obj + i, HEIGHT_N, my_strlen(HEIGHT_N)))
    add->height = get_int_from_node(obj + i, HEIGHT_N);
  if (!my_strncmp(obj + i, REFLECT_N, my_strlen(REFLECT_N)))
    add->reflect = get_pc_from_node(obj + i, REFLECT_N);
  if (!my_strncmp(obj + i, REFRACT_N, my_strlen(REFRACT_N)))
    add->refract = get_pc_from_node(obj + i, REFRACT_N);
  if (!my_strncmp(obj + i, REFR_IDX_N, my_strlen(REFR_IDX_N)))
    add->refr_index = get_pc_from_node(obj + i, REFR_IDX_N);
  if (!my_strncmp(obj + i, SPEC_COEF_N, my_strlen(SPEC_COEF_N)))
    add->spec_coef = get_pint_from_node(obj + i, SPEC_COEF_N);
  if (!my_strncmp(obj + i, SHINE_N, my_strlen(SHINE_N)))
    add->shine = get_int_from_node(obj + i, SHINE_N);
  if (!my_strncmp(obj + i, SCALE_N, my_strlen(SCALE_N)))
    add->scale = get_float_from_node(obj + i, SCALE_N);
  if (!my_strncmp(obj + i, FILE_N, my_strlen(FILE_N)))
    add->file = get_val_from_node(obj + i, FILE_N);
}

static void	attribute_mat(t_p_obj *add,
			      char *str,
			      char *getter,
			      t_material *mat)
{
  t_material	*cur_mat;
  char		*tmp;

  if ((tmp = get_val_from_node(str, getter)) == NULL)
    return ;
  if ((cur_mat = search_material(tmp, mat)) == NULL)
    {
      my_puterror("One material specified in obj doesn't exist.\n");
      return ;
    }
  if (cur_mat->type == 1)
    add->col = cur_mat->color;
  else if (cur_mat->type == 2)
    add->buffer = cur_mat->buf;
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
	add.p1 = get_pos2_from_node(obj + i, P1_N);
      if (!my_strncmp(obj + i, P2_N, my_strlen(P2_N)))
	add.p2 = get_pos2_from_node(obj + i, P2_N);
      if (!my_strncmp(obj + i, MAT_N, my_strlen(MAT_N)))
	attribute_mat(&add, obj + i, MAT_N, mat);
      core_parse_obj(obj, i, &add);
      i += 1;
    }
  if (add.type == -1)
    add.obj_parse = parse_obj_file(add.file);
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
