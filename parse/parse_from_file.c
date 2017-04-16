/*
** parse_from_file.c for parse_from_file in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 18:19:24 2017 
** Last update Fri Apr 14 15:32:58 2017 
*/

#include "raytracer.h"

int	parse_from_file(t_params *params, char *path)
{
  char	**file;

  file = get_file(path);
  parse_material(file);
  /* int	i; */
  /* i = -1; */
  /* while (file[++i]) */
  /*   printf("%s\n", file[i]); */
}
