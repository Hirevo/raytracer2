/*
** args.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 02:43:14 2017 Nicolas Polomack
** Last update Fri Apr 28 11:09:10 2017 Nicolas Polomack
*/

#include <math.h>
#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

static int	get_index(char *flags, char arg)
{
  int		i;

  i = -1;
  while (flags[++i])
    if (flags[i] == arg)
      return (i);
  return (-1);
}

static void	init_links(t_params *params, int *flags[3])
{
  flags[0] = &params->config.stereo;
  flags[1] = &params->config.live;
  flags[2] = &params->help;
  params->help = 0;
  params->config.live = 0;
  params->config.stereo = 0;
  params->config.ssaa = 1;
  params->config.reflect_depth = 3;
  params->config.shadow_rays = 1;
  params->config.depth_rays = 1;
  params->config.fov = 80;
  params->config.scene_file = NULL;
}

static int	get_arg_value(t_params *params, int ac, char **av, int i)
{
  if (my_strcmp(av[i], STEREO) == 0)
    params->config.stereo = 1;
  else if (my_strncmp(av[i], DEPTH, my_strlen(DEPTH)) == 0)
    params->config.reflect_depth = my_getnbr(av[i] + my_strlen(DEPTH));
  else if (my_strncmp(av[i], SSAA, my_strlen(SSAA)) == 0)
    params->config.ssaa = powf(my_getnbr(av[i] + my_strlen(SSAA)), 2);
  else if (my_strncmp(av[i], SOFT, my_strlen(SOFT)) == 0)
    params->config.shadow_rays = my_getnbr(av[i] + my_strlen(SOFT));
  else if (my_strncmp(av[i], DOF, my_strlen(DOF)) == 0)
    params->config.depth_rays = sqrtf(my_getnbr(av[i] + my_strlen(DOF)));
  else if (my_strncmp(av[i], FOV, my_strlen(FOV)) == 0)
    params->config.fov = my_getnbr(av[i] + my_strlen(FOV));
  else
    {
      my_printf("%s: Invalid argument.\n", av[i]);
      return (-1);
    }
  return (0);
}

static int	get_short_arg(char **av, int i, int *flags[3])
{
  int		match;
  int		j;

  j = 0;
  while (av[i][++j])
    if ((match = get_index(ARGS_STR, av[i][j])) == -1)
      return (-1 + 0 *
	      my_printf("-%c: Invalid argument.\n", av[i][j]));
    else
      *(flags[match]) = 1;
}

int		parse_args(t_params *params, int ac, char **av)
{
  int		i;
  int		*flags[3];

  init_links(params, flags);
  i = 0;
  while (++i < ac)
    if (av[i][0] == '-')
      {
	if (av[i][1] != '-')
	  {
	    if (get_short_arg(av, i, flags) == -1)
	      return (-1);
	  }
	else
	  if (get_arg_value(params, ac, av, i) == -1)
	    return (-1);
      }
    else
      {
	if (params->config.scene_file != NULL)
	  return (-1);
	params->config.scene_file = av[i];
      }
  return (0);
}
