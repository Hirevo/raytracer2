/*
** args.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 02:43:14 2017 Nicolas Polomack
** Last update Sat May 27 14:18:08 2017 Cédric THOMAS
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

static void	init_links(t_params *params, int *flags[4])
{
  my_mset(params, 0, sizeof(t_params));
  flags[0] = &params->config.stereo;
  flags[1] = &params->config.live;
  flags[2] = &params->help;
  flags[3] = &params->config.clu_serv;
  params->help = 0;
  params->config.live = 0;
  params->config.stereo = 0;
  params->config.ssaa = 1;
  params->config.tesla = 0;
  params->config.reflect_depth = 3;
  params->config.shadow_rays = 1;
  params->config.depth_rays = 1;
  params->config.fov = 80;
  params->config.clu_cli = NULL;
  params->config.scene_file = NULL;
  params->screen_size.x = 1280;
  params->screen_size.y = 720;
}

static void	get_res(t_params *params, char *str)
{
  int		i;
  int		c;

  i = -1;
  c = 0;
  while (str[++i])
    c += (str[i] == ',');
  if (c != 1)
    {
      my_printf("Incorrect resolution, it has been\
 set to default 1280x720.\n");
      return ;
    }
  i = 0;
  while (str[i] != ',')
    i += 1;
  i += 1;
  params->screen_size.x = my_getnbr(str);
  params->screen_size.y = my_getnbr(str + i);
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
  else if (my_strncmp(av[i], CLUSTERING, my_strlen(CLUSTERING)) == 0)
    params->config.clu_cli = av[i] + my_strlen(CLUSTERING);
  else if (my_strncmp(av[i], TESLA, my_strlen(TESLA)) == 0)
    {
      params->config.tesla = 1;
      params->tesla_lvl = my_getnbr(av[i] + my_strlen(TESLA));
    }
  else if (my_strncmp(av[i], RES, my_strlen(RES)) == 0)
    get_res(params, av[i] + my_strlen(RES));
  else
    return (-1 + 0 * my_printf("%s: Invalid argument.\n", av[i]));
  return (0);
}

static int	get_short_arg(char **av, int i, int *flags[4])
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
  return (0);
}

int		parse_args(t_params *params, int ac, char **av)
{
  int		i;
  int		*flags[4];

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
