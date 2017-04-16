/*
** my_puterror.c for my_puterror in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 19:37:45 2017 
** Last update Thu Apr 13 20:36:40 2017 
*/

#include <unistd.h>

static int	stlen(char *str)
{
  int		i;

  i = -1;
  while (str && str[++i]);
  return (i);
}

int	my_puterror(char *str)
{
  return (write(2, str, stlen(str)));
}
