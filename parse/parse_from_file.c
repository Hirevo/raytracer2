/*
** parse_from_file.c for parse_from_file in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 18:19:24 2017 
** Last update Wed Apr 19 23:20:30 2017 Arthur Knoepflin
*/

#include "raytracer.h"

int		parse_from_file(t_params *params, char *path)
{
  t_p_obj	*obj;
  t_material	*material;
  char		**file;

  file = get_file(path);
  material = parse_material(file);
  parse_light(file, material);
  obj = parse_obj(file, material);
  while (obj)
    {
      printf("======NEW_OBJ======\n");
      printf("\tType : %d\n", obj->type);
      printf("\tPos : %f %f %f\n", obj->pos.x, obj->pos.y, obj->pos.z);
      printf("\tRot : %f %f %f\n", obj->rot.x, obj->rot.y, obj->rot.z);
      printf("\tP1 : %f %f %f\n", obj->p1.x, obj->p1.y, obj->p1.z);
      printf("\tP2 : %f %f %f\n", obj->p2.x, obj->p2.y, obj->p2.z);
      printf("\tRad : %f\n", obj->rad);
      printf("\tAperture : %f\n", obj->aper);
      printf("\tHeight : %f\n", obj->height);
      obj = obj->next;
    }
}
