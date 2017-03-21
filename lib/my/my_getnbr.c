/*
** my_getnbr.c for my_getnbr in /home/nicolas.polomack/CPool_Day04
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Thu Oct  6 17:52:30 2016 Nicolas POLOMACK
** Last update Fri Jan  6 00:18:02 2017 Nicolas Polomack
*/

#include "my.h"

int	get_nbr_len(char *arr, int count)
{
  int	nbr_len;
  int	test_count;
  int	total;

  total = 0;
  test_count = 0;
  nbr_len = 1;
  while (*(arr + count) >= 48 && *(arr + count) <= 57)
    {
      nbr_len *= 10;
      total += *(arr + count) - 48;
      count += 1;
    }
  if (my_strlen(arr) >= 9 && total > 46)
      nbr_len = 0;
  return (nbr_len);
}

int	my_getnbr(char *file)
{
  int	result;
  int	i;
  int	factor;
  int	c;
  int	isNegative;

  isNegative = 1;
  i = 0;
  if (file[i] == '-')
    isNegative *= ((file[i] == '-') ? -1 : 1) + (i += 1) * 0;
  c = i + (factor = 1) * 0;
  result = 0;
  while (file[c] >= '0' && file[c] <= '9')
    {
      factor *= 10;
      c += 1;
    }
  factor /= 10;
  while (file[i] >= '0' && file[i] <= '9')
    {
      result += (file[i] - '0') * factor;
      factor /= 10;
      i += 1;
    }
  return (result * isNegative);
}
