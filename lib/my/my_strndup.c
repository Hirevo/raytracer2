/*
** my_strndup.c for my_strndup in /home/arthur/PSU_2016_minishell2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Sat Mar 25 23:02:17 2017 Arthur Knoepflin
** Last update Sat Mar 25 23:02:18 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "my.h"

char	*my_strndup(char *src, int len)
{
  char	*resp;
  int	count;

  count = 0;
  resp = malloc(sizeof(char) * (my_strlen(src) + 1));
  if (resp == NULL)
    return (NULL);
  while (src[count] != '\0' && count < len)
    {
      resp[count] = src[count];
      count = count + 1;
    }
  resp[count] = '\0';
  return (resp);
}
