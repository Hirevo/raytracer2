/*
** convert_base.c for convert_base in /home/nicolas/psu/PSU_2016_my_printf/
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Mon Nov 14 10:47:52 2016 Nicolas Polomack
** Last update Wed Mar 29 01:49:55 2017 Nicolas Polomack
*/

#include "my.h"

char	*my_custom_revstr(char *str, int isNegative)
{
  int   count;
  int   reverse_count;
  char  resp[my_strlen(str) + 2];

  count = 0;
  reverse_count = my_strlen(str) - 1;
  if (isNegative == (-1))
    {
      resp[0] = '-';
      count = 1;
    }
  while (reverse_count >= 0 &&
	 str[reverse_count] != '\0')
    {
      resp[count] = str[reverse_count];
      reverse_count = reverse_count - 1;
      count = count + 1;
    }
  resp[count] = '\0';
  return (my_strdup(resp));
}

char	*my_algorithm(int nbr, char *symbols, int base, int isNegative)
{
  int	i;
  int	n;
  char	total[base];
  int	factor;

  i = nbr / base;
  n = nbr % base;
  nbr = nbr / base;
  total[0] = symbols[n];
  factor = 1;
  while (i != 0)
    {
      i = nbr / base;
      n = nbr % base;
      nbr = nbr / base;
      total[factor] = symbols[n];
      factor = factor + 1;
    }
  total[factor] = '\0';
  return (my_custom_revstr(total, isNegative));
}

int	get_val(char symb, char *base_from)
{
  int	count;

  count = 0;
  while (base_from[count] != symb)
    count = count + 1;
  return (count);
}

char	*convert_base(char *nbr, char *base_from, char *base_to)
{
  int	base1;
  int	base2;
  int	size;
  int	factor;
  int	total;
  int	isNegative;

  factor = 1;
  size = my_strlen(nbr) - 1;
  base1 = my_strlen(base_from);
  base2 = my_strlen(base_to);
  total = 0;
  while (size >= 0 && nbr[size] != '-')
    {
      total = total + (get_val(nbr[size], base_from) * factor);
      factor = factor * base1;
      size = size - 1;
    }
  isNegative = 1;
  if (nbr[0] == '-')
    {
      isNegative = (-1);
      factor = factor / base1;
    }
  return (my_algorithm(total, base_to, base2, isNegative));
}
