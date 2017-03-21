/*
** my_find_prime_sup.c for my_find_prime_sub in /home/nicolas.polomack/CPool_Day05
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Fri Oct  7 14:06:56 2016 Nicolas POLOMACK
** Last update Tue Nov 22 17:25:57 2016 Nicolas Polomack
*/

#include "my.h"

int	my_find_prime_sub(int nb)
{
  if (nb <= 0)
    return (2);
  while (my_is_prime(nb) != 1 && nb < 2147483648)
    {
      nb = nb + 1;
      if (nb == 2147483648)
	return (0);
    }
  return (nb);
}
