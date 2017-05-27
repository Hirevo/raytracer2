/*
** count_the_place.c for count_the_place in /home/Maxime/perso/echat/lib/socket/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu May  4 17:40:13 2017 Maxime Jenny
** Last update	Sat May 27 21:20:35 2017 Full Name
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "socket_lib.h"
#include "server.h"

int	count_place(t_SOCKET fd, long size)
{
  off_t	actual;
  char	str[size];

  if ((actual = recv(fd, str, size, MSG_PEEK | MSG_DONTWAIT)) == -1)
    {
      if (errno != EAGAIN)
	return (-1);
    }
  if (actual == size)
    return (1);
  return (0);
}
