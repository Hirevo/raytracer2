/*
** protocol.c for proto in /home/Maxime/perso/echat/lib/t_SOCKET/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Tue May  2 15:07:24 2017 Maxime Jenny
** Last update	Sat May 27 21:22:22 2017 Full Name
*/

#include <sys/ioctl.h>
#include <termio.h>
#include <fcntl.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "my.h"
#include "socket_lib.h"

char	*my_strconcat(char *dest, char *src)
{
  int	i;
  int	m;
  char	*str;

  if ((str = malloc(my_strlen(dest) + my_strlen(src) + 1)) == NULL)
    return (NULL);
  while (dest && dest[i] != '\0')
    {
      str[i] = dest[i];
      i++;
    }
  while (src && src[m])
    str[i++] = src[m++];
  str[i] = 0;
  free(dest);
  return (str);
}

char		*recup_size(long size, char *size_msg)
{
  int		i;

  i = 0;
  while (i < 8)
    size_msg[i++] = '0';
  size_msg[i--] = 0;
  while (i >= 0)
    {
      size_msg[i--] = (size % 10) + '0';
      size /= 10;
    }
  return (size_msg);
}

int		send_protocol(t_SOCKET csock, void *msg, long size, int flags)
{
  char		*size_msg;
  int		i;

  i = 0;
  if ((size_msg = malloc(9)) == NULL)
    return (-1);
  size_msg = recup_size(size, size_msg);
  size_msg = my_strconcat(size_msg, msg);
  if ((send(csock, size_msg, size + 8, flags)) == -1)
    return (my_put_error("send()", -1));
  return (0);
}

int		recv_protocol(t_SOCKET sock, void **msg, long *len, int flags)
{
  int		n;
  char		size[9];

  *msg = NULL;
  while (count_place(sock, 8) != 1);
  if ((n = recv(sock, size, 8, flags)) == -1)
    return ((errno != EAGAIN) ? (my_put_error("recv()", -1)) : (0));
  else
    {
      size[8] = 0;
      while (count_place(sock, my_getnbr(size)) != 1);
      if (((*msg) = malloc(my_getnbr(size) + 1)) == NULL)
	return (-1);
      if ((n = recv(sock, *msg, my_getnbr(size), flags)) == -1)
	{
	  free(*msg);
	  *msg = NULL;
	  return ((errno != EAGAIN) ? (my_put_error("recv()", -1)) : (0));
	}
      ((char *)(*msg))[n] = 0;
      *len = my_getnbr(size);
    }
  return (0);
}
