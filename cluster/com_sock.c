/*
** com_sock.c for com_sock in /home/arthur/delivery/PSU/PSU_2016_42sh
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sun May  7 17:30:59 2017 Arthur Knoepflin
** Last update Wed May 24 20:14:04 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "my.h"

static char	*concat_com(char *str1, char *str2, int size)
{
  int		i;
  int		j;
  int		len;
  char		*ret;

  len = (str1 == NULL) ? size : my_strlen(str1) + size;
  if ((ret = malloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  ret[len] = '\0';
  i = 0;
  while (str1 && str1[i])
    {
      ret[i] = str1[i];
      i += 1;
    }
  j = 0;
  while (j < size)
    {
      ret[i] = str2[j];
      i += 1;
      j += 1;
    }
  ret[i] = '\0';
  return (ret);
}

int		read_socket(t_socket sock, char **ret)
{
  char		tmp[SIZE_SOCK];
  size_t	len;

  *ret = NULL;
  while ((len = recv(sock, tmp, SIZE_SOCK, 0)) == SIZE_SOCK)
    {
      *ret = concat_com(*ret, tmp, len);
    }
  *ret = concat_com(*ret, tmp, len);
  return (my_strlen(*ret));
}

void	write_socket(t_socket sock, char *str)
{
  if (str)
    {
      if (send(sock, str, my_strlen(str), 0) < 0)
	perror("send");
    }
}
