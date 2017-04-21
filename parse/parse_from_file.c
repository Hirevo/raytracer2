/*
** parse_from_file.c for parse_from_file in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 18:19:24 2017 
** Last update Fri Apr 21 14:30:32 2017 Arthur Knoepflin
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
  /* tmp_light = light->light; */
  /* printf("Ambient : %f\n", light->ambient); */
  /* while (tmp_light) */
  /*   { */
  /*     printf("======NEW LIGHT=======\n"); */
  /*     printf("\tPos : %f %f %f\n", tmp_light->pos.x, tmp_light->pos.y, tmp_light->pos.z); */
  /*     printf("\tCol : %d %d %d\n", tmp_light->col.r, tmp_light->col.g, tmp_light->col.b); */
  /*     tmp_light = tmp_light->next; */
  /*   } */
  /* while (material) */
  /*   { */
  /*     printf("======NEW MATERIAL=======\n"); */
  /*     printf("\tType : %d\n", material->type);       */
  /*     printf("\tName : %s\n", material->name); */
  /*     printf("\tColor : %d %d %d\n", material->color.r, material->color.g, material->color.b); */
  /*     printf("\tPath : %s\n", material->path); */
  /*     printf("\tBuf : %s\n", material->buf); */
  /*     material = material->next; */
  /*   } */
  /* while (obj) */
  /*   { */
  /*     printf("======NEW_OBJ======\n"); */
  /*     printf("\tType : %d\n", obj->type); */
  /*     printf("\tPos : %f %f %f\n", obj->pos.x, obj->pos.y, obj->pos.z); */
  /*     printf("\tRot : %f %f %f\n", obj->rot.x, obj->rot.y, obj->rot.z); */
  /*     printf("\tP1 : %f %f %f\n", obj->p1.x, obj->p1.y, obj->p1.z); */
  /*     printf("\tP2 : %f %f %f\n", obj->p2.x, obj->p2.y, obj->p2.z); */
  /*     printf("\tRad : %f\n", obj->rad); */
  /*     printf("\tColor : %d %d %d\n", obj->col.r, obj->col.g, obj->col.b); */
  /*     printf("\tBuffer : %p\n", obj->buffer); */
  /*     printf("\tAperture : %f\n", obj->aper); */
  /*     printf("\tHeight : %f\n", obj->height); */
  /*     printf("\tReflect : %f\n", obj->reflect); */
  /*     printf("\tRefract : %f\n", obj->refract); */
  /*     printf("\tRefract index : %f\n", obj->refr_index); */
  /*     printf("\tCoefficient de spécularité : %f\n", obj->spec_coef); */
  /*     obj = obj->next; */
  /*   } */
  return (0);
}
