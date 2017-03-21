/*
** my_strupcase.c for my_strupcase in /home/nicolas.polomack/CPool_Day06
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Mon Oct 10 12:10:37 2016 Nicolas POLOMACK
** Last update Wed Nov 23 13:51:57 2016 Nicolas Polomack
*/

int	my_str_isnum(char *str)
{
  int	count;

  count = 0;
  while (str[count] != 0)
    {
      if ((str[count] == '-' && count != 0) ||
      	(str[count] < '0' || str[count] > '9'))
	return (0);
      count += 1;
    }
  return (1);
}
