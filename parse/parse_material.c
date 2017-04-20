/*
** parse_material.c for material in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 23:05:29 2017 
** Last update Thu Apr 20 21:27:22 2017 Arthur Knoepflin
*/

#include "raytracer.h"
#include "bmp.h"
#include "my.h"

static void	parse_color_material(t_material **ret, char *obj, int *i)
{
  t_material	add;

  my_mset(&add, 0, sizeof(add));
  add.type = 1;
  while (obj[*i] && my_strncmp(obj + *i, "/>", 2))
    {
      if (!my_strncmp(obj + *i, NAME_N, my_strlen(NAME_N)))
	if ((add.name = get_val_from_node(obj + *i, NAME_N)) == NULL)
	  return ;
      if (!my_strncmp(obj + *i, COLOR_N, my_strlen(COLOR_N)))
	add.color = get_color_from_node(obj + *i, COLOR);
      *i += 1;
    }
  add_material(ret, add);
}

static void	parse_text_material(t_material **ret, char *obj, int *i)
{
  t_material	add;

  my_mset(&add, 0, sizeof(add));
  add.type = 2;
  add.color.r = 255;
  add.color.g = 255;
  add.color.b = 255;
  add.color.a = 255;
  while (obj[*i] && my_strncmp(obj + *i, "/>", 2))
    {
      if (!my_strncmp(obj + *i, NAME_N, my_strlen(NAME_N)))
	if ((add.name = get_val_from_node(obj + *i, NAME_N)) == NULL)
	  return ;
      if (!my_strncmp(obj + *i, TEXT_N, my_strlen(TEXT_N)))
	{
	  if ((add.path = get_val_from_node(obj + *i, TEXT_N)) == NULL)
	    return ;
	  add.buf = load_bmp(add.path, NULL, NULL);
	}
      *i += 1;
    }
  add_material(ret, add);
}

t_material	*parse_material(char **file)
{
  char		*get_obj;
  int		i;
  t_material	*ret;
  t_material	*tmp;

  ret = NULL;
  if ((get_obj = get_head_node(file, MATERIAL)) == NULL)
    return (NULL);
  i = 0;
  while (get_obj[i])
    {
      if (!my_strncmp(get_obj + i, COLOR, my_strlen(COLOR)))
	parse_color_material(&ret, get_obj, &i);
      if (!my_strncmp(get_obj + i, TEXT, my_strlen(TEXT)))
	parse_text_material(&ret, get_obj, &i);
      if (get_obj[i])
	i += 1;
    }
  return (ret);
}
