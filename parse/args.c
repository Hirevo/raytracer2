/*
** args.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 02:43:14 2017 Nicolas Polomack
** Last update Thu Mar 30 13:49:44 2017 Nicolas Polomack
*/

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

static void	init_links(t_params *params, int *flags[2])
{
  flags[0] = &params->config.stereo;
  flags[1] = &params->config.live;
}

void		parse_args(t_params *params, int ac, char **av)
{
  int		i;
  int		j;
  int		match;
  int		*flags[2];

  params->config.stereo = 0;
  params->config.live = 0;
  init_links(params, flags);
  i = 0;
  while (++i < ac)
    if (av[i][0] == '-')
      {
	if (av[i][1] != '-')
	  {
	    j = 0;
	    while (av[i][++j])
	      if ((match = get_index("Su", av[i][j])) == -1)
		exit(84 + 0 * my_printf("-%c: Invalid argument.\n", av[i][j]));
	      else
		*(flags[match]) = 1;
	  }
	else
	  if (my_strcmp(av[i], "--stereo") == 0)
	    params->config.stereo = 1;
      }
}
