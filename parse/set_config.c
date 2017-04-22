/*
** set_config.c for set_config in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 21 13:04:16 2017 Arthur Knoepflin
** Last update Sat Apr 22 18:46:43 2017 Nicolas Polomack
*/

#include "raytracer.h"

void	set_config(t_params *ret, t_p_light *light)
{
  ret->config.ambient = light->ambient;
}
