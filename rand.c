/*
** rand.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/multithread
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Mar  1 10:52:23 2017 Nicolas Polomack
** Last update Fri Mar 31 15:24:17 2017 Nicolas Polomack
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int			my_rand(long int seed)
{
  static unsigned int	state[4] = {0, 0, 0, 0};
  unsigned int		t;

  if (state[0] == 0 && state[1] == 0 && state[2] == 0 && state[3] == 0)
    {
      my_memcpy(state, &seed, 8);
      seed = (seed * -1) ^ 0x2345;
      my_memcpy(&(state[2]), &seed, 8);
    }
  t = state[3];
  t ^= t << 11;
  t ^= t >> 8;
  state[3] = state[2];
  state[2] = state[1];
  state[1] = state[0];
  t ^= state[0];
  t ^= state[0] >> 19;
  state[0] = t;
  return (t);
}

long int	init_seed(int ac, char **av, char **env, void *main)
{
  int		lel;
  void		*mem;
  void		*bonus;
  long int	seed;

  (void)av;
  mem = malloc(0);
  free(bonus = malloc(0));
  free(mem);
  seed = ((((((long int)mem | (long int)bonus) / (long int)&lel) +
	    (long int)main) - ((long int)&ac + 1)) * ((long int)(&env) / 2));
  return (seed);
}
