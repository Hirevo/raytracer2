/*
** args.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 02:43:14 2017 Nicolas Polomack
** Last update Thu Mar 30 02:51:08 2017 Nicolas Polomack
*/

#include "raytracer.h"
#include "my.h"

void		parse_args(t_params *params, int ac, char **av)
{
  int		i;

  params->config.stereo = 0;
  i = 0;
  while (++i < ac)
    {
      if (my_strcmp(av[i], "-3d") == 0 ||
	  my_strcmp(av[i], "--stereo") == 0)
	params->config.stereo = 1;
    }
}
