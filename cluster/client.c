/*
** client.c for client in /home/Maxime/delivery/MUL/raytracer2/cluster/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu May 25 13:22:50 2017 Maxime Jenny
** Last update	Thu May 25 13:23:11 2017 Full Name
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
#include "socket_lib.h"

int		print_state_wait(t_socket sock)
{
  fd_set	rdfs;
  char		*actual;
  char		*max;

  write_socket(sock, "nb_cli_act");
  read_socket(sock, &actual);
  write_socket(sock, "nb_cli_max");
  read_socket(sock, &max);
  if (actual && max)
    my_printf("\rWait for client %s[%s/%s]\033[0m",
	      (my_strcmp(actual, max)) ? "\033[31;1m" : "\033[32;1m",
	      actual, max);
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
      my_printf("\nImpossible to find %s\n", addr);
      return (1);
    }
  sin.sin_addr = *(t_in_addr *) hostinfo->h_addr;
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;
  if (connect(*sock, (t_sockaddr *) &sin, sizeof(t_sockaddr)) == -1)
    {
      my_printf("\nImpossible to connect %s\n", addr);
      return (1);
    }
  my_putstr("\nConnected\n");
  print_state_wait(*sock);
  return (0);
}

static int	treat_resp_wait_c(t_socket sock)
{
  char		*talk;

  if (read_socket(sock, &talk) == 0)
    {
      my_putstr("\nDisconnected, abort clustering\n");
      return (1);
    }
  else
    return (treat_resp(sock, talk));
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

int		client_cluster(t_window *w, t_params *p)
{
  t_socket	sock;
  long		n;
  t_zone	zone;

  if (connect_cli(p->config.clu_cli, &sock))
    return (84);
  if (wait_connect_c(sock))
    return (84);
  recv(sock, &zone, sizeof(t_zone), 0);
  send(sock, "ok", 2, 0);
  my_printf("You recieved :\nstart: %d; %d\nend: %d; %d\n", zone.s_x,
	    zone.s_y, zone.e_x, zone.e_y);
  close(sock);
  return (0);
}
