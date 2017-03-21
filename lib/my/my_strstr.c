/*
** my_strstr.c for my_strstr in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 09:38:55 2016 Nicolas POLOMACK
** Last update Tue Oct 11 09:00:57 2016 Nicolas POLOMACK
*/

#include <stdlib.h>

char	*my_strstr(char *str, char *to_find)
{
  int	count;
  int	to_find_count;

  count = 0;
  to_find_count = 0;
  while (*str != '\0')
    {
      while (*(str + count) == *(to_find + to_find_count) &&
	     *(to_find + to_find_count) != '\0')
	{
	  count = count + 1;
	  if (*(to_find + to_find_count + 1) == '\0')
	      return (str);
	  to_find_count = to_find_count + 1;
	}
      str = str + count + 1;
      count = 0;
      to_find_count = 0;
    }
  return (NULL);
}
