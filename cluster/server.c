/*
** server.c for server in /home/arthur/delivery/MUL/raytracer2
**
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
**
** Started on  Wed May 24 09:23:35 2017 Arthur Knoepflin
** Last update	Thu May 25 13:23:03 2017 Full Name
*/

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"
#include "my.h"
#include "socket_lib.h"

static int	init_serv(t_socket *sock)
{
  t_sockaddr_in	sin;

  if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (1);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;
  if (bind(*sock, (t_sockaddr *) &sin, sizeof(sin)) == -1)
    {
      close(*sock);
      return (1);
    }
  if (listen(*sock, CLIENTS) == -1)
    {
      close(*sock);
      return (1);
    }
  return (0);
}

void	broadcast_start(t_client *clients)
{
  char	*buf;
  int	i;

  i = 0;
  my_printf("\nStart !!\n");
  while (i < CLIENTS)
    {
      write_socket(clients[i].sock, "start");
      read_socket(clients[i].sock, &buf);
      free(buf);
      i += 1;
    }
}

static int	send_zones(t_client *clients, t_params *p)
{
  int		i;

  send_parse(clients, p);
  divide_scene(clients, &p->screen_size, CLIENTS);
  i = 0;
  while (i < CLIENTS)
    {
      if ((send_protocol(clients[i].sock, (void *)&clients[i].zone,
  			 sizeof(clients[i].zone), MSG_DONTWAIT)) == -1)
  	return (-1);
      i++;
    }
}

int		server_cluster(t_window *w, t_params *p)
{
  t_client	clients[CLIENTS];
  char		*ip;
  int		nb_cli_conn;
  t_socket	serv;

  if (init_serv(&serv))
    return (84);
  ip = get_ip();
  my_printf("\nServer started on \033[32;1m%s\033[0m...\n", (ip) ? ip :
	    "\033[31;1munknown\033[0m");
  my_printf("Wait for client \033[31;1m[0/%d]\033[0m", CLIENTS);
  free(ip);
  if ((nb_cli_conn = wait_connection_s(clients, serv)) != -1)
    {
      close_all(clients, nb_cli_conn);
      return (84);
    }
  send_zones(clients, p);
  close_all(clients, CLIENTS);
  close(serv);
  return (0);
}
