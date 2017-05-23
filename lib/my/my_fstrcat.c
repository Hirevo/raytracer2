/*
** my_strcatdup.c for my_strcatdup in /home/arthur/delivery/PSU/PSU_2016_tetris
** 
** Made by 
** Login   <arthur@epitech.net>
** 
** Started on  Tue Feb 21 10:22:56 2017 
** Last update Tue May 16 10:06:30 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "my.h"

static void	copy_data(char *dest, char *s1, char *s2)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (s1[i])
    {
      dest[i] = s1[i];
      i += 1;
    }
  j = 0;
  while (s2[j])
    {
      dest[i] = s2[j];
      i += 1;
      j += 1;
    }
  dest[i] = '\0';
}

char	*my_fstrcat(char *s1, char *s2, int mode)
{
  int	i;
  int	j;
  char	*dest;
  int	len;

  i = 0;
  len = 0;
  if (s1 != NULL)
    len = my_strlen(s1);
  if (s2 != NULL)
    len += my_strlen(s2);
  if ((dest = malloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  copy_data(dest, s1, s2);
  if (mode == 1 || mode == 2)
    free(s1);
  if (mode == 2 || mode == 3)
    free(s2);
  return (dest);
}
