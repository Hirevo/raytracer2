/*
** parse_from_file.c for parse_from_file in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 18:19:24 2017 
** Last update Wed May 10 17:36:40 2017 Nicolas Polomack
*/

#include "raytracer.h"

int		parse_from_file(t_params *params, char *path)
{
  t_p_obj	*obj;
  t_p_light	*light;
  t_material	*material;
  char		**file;

  file = get_file(path);
  set_camera(params, file);
  if ((material = parse_material(file)) == NULL)
    return (1);
  if ((light = parse_light(file, material)) == NULL)
    return (1);
  if ((obj = parse_obj(file, material)) == NULL)
    return (1);
  set_config(params, light);
  if (convert_light(params, light->light))
    return (1);
  if (convert_obj(params, obj))
    return (1);
  return (0);
}
