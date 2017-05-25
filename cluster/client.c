/*
** client.c for client in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 15:13:00 2017 Arthur Knoepflin
** Last update Thu May 25 18:54:35 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include "server.h"
#include "get_next_line.h"
#include "my.h"

int		print_state_wait(t_socket sock)
{
  fd_set	rdfs;
  char		*actual;
  char		*max;

  write_socket(sock, "nb_cli_act");
  read_socket(sock, &actual);
  write_socket(sock, "nb_cli_max");
  read_socket(sock, &max);
  my_printf("\rWait for client [%s/%s]", actual, max);
  if (!my_strcmp(actual, max))
    {
      free(max);
      write_socket(sock, "ready");
      read_socket(sock, &max);
    }
  free(actual);
  free(max);
}

static int		connect_cli(char *addr, t_socket *sock)
{
  t_sockaddr_in		sin;
  struct hostent	*hostinfo;

  if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (1);
  if ((hostinfo = gethostbyname(addr)) == NULL)
    {
      my_printf("Impossible to find %s\n", addr);
      return (1);
    }
  sin.sin_addr = *(t_in_addr *) hostinfo->h_addr;
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;
  if (connect(*sock, (t_sockaddr *) &sin, sizeof(t_sockaddr)) == -1)
    {
      my_printf("Impossible to connect %s\n", addr);
      return (1);
    }
  my_putstr("Connected\n");
  print_state_wait(*sock);
  return (0);
}

static int	treat_resp_wait_c(t_socket sock)
{
  char		*talk;

  if (read_socket(sock, &talk) == 0)
    {
      my_putstr("Disconnected, abort clustering\n");
      return (1);
    }
  else
    treat_resp(sock, talk);
  return (0);
}

static int	wait_connect_c(t_socket sock)
{
  fd_set	rdfs;
  int		stop;

  stop = 0;
  while (!stop)
    {
      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(sock, &rdfs);
      if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
	return (1);
      if (FD_ISSET(STDIN_FILENO, &rdfs))
	stop = 2;
      else if (FD_ISSET(sock, &rdfs))
	stop = treat_resp_wait_c(sock);
    }
  if (stop == 2)
    {
      free(get_next_line(0));
      return (1);
    }
  return (0);
}

int		client_cluster(t_params *p, t_window *w)
{
  t_socket	sock;

  if (connect_cli(p->config.clu_cli, &sock))
    return (84);
  if (wait_connect_c(sock))
    return (84);
  return (0);
}
