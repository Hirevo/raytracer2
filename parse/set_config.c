/*
** set_config.c for set_config in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri Apr 21 13:04:16 2017 Arthur Knoepflin
** Last update Fri Apr 21 15:58:27 2017 Arthur Knoepflin
*/

#include "raytracer.h"

void	set_config(t_params *ret, t_p_light *light)
{
  ret->config.ssaa = 1;
  ret->config.reflect_depth = 3;
  ret->config.depth_rays = 1;
  ret->config.fov = 80;
  ret->config.ambient = light->ambient;
}
