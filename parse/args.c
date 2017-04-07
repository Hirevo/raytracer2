/*
** args.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Mar 30 02:43:14 2017 Nicolas Polomack
** Last update Fri Apr  7 16:53:57 2017 Nicolas Polomack
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

static void	init_links(t_params *params, int *flags[3])
{
  flags[0] = &params->config.stereo;
  flags[1] = &params->config.live;
  flags[2] = &params->help;
}

void		parse_args(t_params *params, int ac, char **av)
{
  int		i;
  int		j;
  int		match;
  int		*flags[3];

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
	      if ((match = get_index("Suh", av[i][j])) == -1)
		exit(84 + 0 * my_printf("-%c: Invalid argument.\n", av[i][j]));
	      else
		*(flags[match]) = 1;
	  }
	else
	  if (my_strcmp(av[i], "--stereo") == 0)
	    params->config.stereo = 1;
      }
}
