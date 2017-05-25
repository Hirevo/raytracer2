/*
** my_getnbr.c for my_getnbr in /home/nicolas.polomack/CPool_Day04
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Thu Oct  6 17:52:30 2016 Nicolas POLOMACK
** Last update Wed Feb 22 09:54:28 2017 Nicolas Polomack
*/

#include "my.h"

int	my_getnbr(char *str)
{
  int	i;
  int	factor;
  int	total;
  int	is_neg;

  factor = 1;
  i = 0;
  total = 0;
  is_neg = 1;
  while (*str == '+' || *str == '-')
    if (*(str++) == '-')
      is_neg *= -1;
  while (str[i] >= '0' && str[i] <= '9')
    i += 1;
  i -= 1;
  while (i >= 0)
    {
      total += (str[i] - '0') * factor;
      factor *= 10;
      i -= 1;
    }
  return (total * is_neg);
}
