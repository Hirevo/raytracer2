/*
** percent.c for percent in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Fri May 26 10:39:57 2017 Arthur Knoepflin
** Last update Fri May 26 13:59:11 2017 Arthur Knoepflin
*/

#include "server.h"
#include "my.h"



void	print_percent(int pc)
{
  int	i;
  char	*str;
  int	size;

  size = (pc * PERCENT) / 100;
  str = my_int_to_char(pc);
  my_putstr("\r[");
  i = 0;
  while (i < PERCENT)
    {
      if (i == (PERCENT / 2) - (my_strlen(str) / 2))
	{
	  my_printf("\033[31;1m%s\033[0m", str);
	  i += my_strlen(str);
	}
      else if (i < size)
	my_putchar('#');
      else
	my_putchar(' ');
      i += 1;
    }
  my_putchar(']');
}
