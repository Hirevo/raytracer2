/*
** my_square_root.c for my_square_root in /home/nicolas.polomack/CPool_Day05
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Fri Oct  7 11:50:43 2016 Nicolas POLOMACK
** Last update Fri Dec 23 23:39:07 2016 Nicolas Polomack
*/

int	my_square_root(int nb)
{
  int	interval;

  if (nb == 0)
    return (0);
  else if (nb == 1)
    return (1);
  else if (nb < 0)
    return (0);
  else
    {
      interval = nb / 2;
      if (nb > 10000)
	interval = nb / 100;
      if (nb > 1000000)
	interval = nb / 1000;
      if (nb > 1000000)
	interval = nb / 10000;
      while ((interval * interval) != nb && interval > 0)
	{
	  interval = interval - 1;
	}
      return (interval);
    }
}
