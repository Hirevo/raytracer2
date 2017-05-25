/*
** server.c for server in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 09:23:35 2017 Arthur Knoepflin
** Last update Thu May 25 11:24:02 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"
#include "my.h"

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

int		server_cluster(t_window *w, t_params *p)
{
  t_client	clients[CLIENTS];
  char		*ip;
  int		nb_cli_conn;
  t_socket	serv;

  if (init_serv(&serv))
    return (84);
  ip = get_ip();
  my_printf("\nServer started on \033[32;1m%s\033[0m...\n\
Wait for client \033[31;1m[0/%d]\033[0m",
	    (ip) ? ip : "\033[31;1munknown\033[0m", CLIENTS);
  free(ip);
  if ((nb_cli_conn = wait_connection_s(clients, serv)))
    {
      close_all(clients, nb_cli_conn);
      return (84);
    }
  send_parse(clients, p);
  close_all(clients, CLIENTS);
  close(serv);
  return (0);
}
