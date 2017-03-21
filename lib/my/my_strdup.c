/*
** my_strdup.c for my_strdup in /home/nicolas.polomack/CPool_Day08
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Wed Oct 12 09:23:05 2016 Nicolas POLOMACK
** Last update Thu Feb  2 00:30:51 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include "my.h"

char	*my_strdup(char *src)
{
  char	*resp;
  int	count;

  count = 0;
  resp = malloc(sizeof(char) * (my_strlen(src) + 1));
  if (resp == NULL)
    return (NULL);
  while (src[count] != '\0')
    {
      resp[count] = src[count];
      count = count + 1;
    }
  resp[count] = '\0';
  return (resp);
}

char	**my_strarrdup(char **arr)
{
  char	**final;
  int	i;

  i = -1;
  while (arr[++i]);
  if ((final = malloc(sizeof(char *) * (i + 1))) == NULL)
    return (NULL);
  i = -1;
  while (arr[++i])
    final[i] = my_strdup(arr[i]);
  final[i] = NULL;
  return (final);
}

