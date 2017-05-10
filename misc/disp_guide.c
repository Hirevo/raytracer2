/*
** help.c for raytracer2 in 
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Apr  7 16:46:51 2017 Nicolas Polomack
** Last update Wed May 10 16:51:05 2017 Nicolas Polomack
*/

#include "my.h"
#include "help.h"

int	disp_guide()
{
  extern unsigned char	help_txt[];
  extern unsigned int	help_txt_len;
  int			i;

  i = -1;
  while (++i < help_txt_len)
    my_putchar(help_txt[i]);
  return (0);
}
