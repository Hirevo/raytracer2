/*
** my_sort_int_table.c for my_sort_int_tab in /home/nicolas.polomack/recovery
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Fri Oct 14 10:17:09 2016 Nicolas POLOMACK
** Last update Tue Nov 22 18:14:53 2016 Nicolas Polomack
*/

#include "my.h"

int	*my_sort_int_tab(int *tab, int size)
{
  int	trouble;
  int	i;

  trouble = 1;
  while (trouble)
    {
      i = 0;
      trouble = 0;
      while (i < size)
	{
	  if (tab[i] > tab[i + 1])
	    {
	      my_swap(tab[i], tab[i + 1]);
	      trouble = 1;
	    }
	  i = i + 1;
	}
    }
  return (tab);
}
