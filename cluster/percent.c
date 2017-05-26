/*
** percent.c for percent in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 26 10:39:57 2017 Arthur Knoepflin
** Last update Fri May 26 10:59:59 2017 Nicolas Polomack
*/

#include "server.h"
#include "my.h"

void	print_percent(int pc)
{
  int	i;
  int	size;

  size = (pc * PERCENT) / 100;
  my_putstr("\r[");
  i = 0;
  while (i < PERCENT)
    {
      if (i < size)
	my_putchar('#');
      else
	my_putchar(' ');
      i += 1;
    }
  my_putchar(']');
}
