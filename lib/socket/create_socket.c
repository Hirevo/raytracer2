/*
** create_socket.c for create in /home/Maxime/perso/echat/lib/socket/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Tue May  2 15:05:07 2017 Maxime Jenny
** Last update	Thu May 25 11:08:32 2017 Full Name
*/

#include <unistd.h>
#include "socket_lib.h"

int		create_socket(void)
{
  SOCKET	sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock == INVALID_SOCKET)
    {
      write(2, "An error occured with create_socket.\n", 37);
      return (-1);
    }
  return (sock);
}
