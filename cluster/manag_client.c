/*
** manag_client.c for manag_client in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 13:33:41 2017 Arthur Knoepflin
** Last update Fri May 26 01:46:12 2017 Arthur Knoepflin
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void	remove_client(t_client *clients,
		      int to_rem,
		      int *actual,
		      int mode)
{
  char	*buf;
  int	i;

  i = 0;
  close(clients[to_rem].sock);
  memmove(clients + to_rem, clients + to_rem + 1,
	  (*actual - to_rem - 1) * sizeof(t_client));
  (*actual) -= 1;
  if (*actual < 0)
    *actual = 0;
  if (mode == 1)
    {
      while (i < *actual)
	{
	  write_socket(clients[i].sock, "rm_cli");
	  read_socket(clients[i].sock, &buf);
	  free(buf);
	  i += 1;
	}
    }
}

void	close_all(t_client *clients, int actual)
{
  int	i;

  i = 0;
  while (i < actual)
    {
      close(clients[i].sock);
      i += 1;
    }
}
