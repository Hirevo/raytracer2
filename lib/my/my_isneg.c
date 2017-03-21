/*
** my_isneg.c for my_isneg in /home/nicolas.polomack/CPool_Day03
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Wed Oct  5 10:43:39 2016 Nicolas POLOMACK
** Last update Tue Nov 22 18:03:34 2016 Nicolas Polomack
*/

#include "my.h"

int	my_isneg(int n)
{
  if (n < 0)
    my_putchar('N');
  else
    my_putchar('P');
}
