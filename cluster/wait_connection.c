/*
** wait_connection.c for wait_connection in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 10:31:37 2017 Arthur Knoepflin
** Last update Thu May 25 16:01:11 2017 Arthur Knoepflin
*/

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"
#include "get_next_line.h"
#include "my.h"

static int	set_select(fd_set *rdfs,
			   t_client *clients,
			   int *actual,
			   t_socket sock)
{
  int		i;

  i = 0;
  FD_ZERO(rdfs);
  FD_SET(STDIN_FILENO, rdfs);
  FD_SET(sock, rdfs);
  while (i < *actual)
    {
      FD_SET(clients[i].sock, rdfs);
      i += 1;
    }
  if (*actual ==  0)
    {
      if (select(sock + 1, rdfs, NULL, NULL, NULL) == -1)
	return (1);
    }
  else
    if (select(clients[*actual - 1].sock + 1,
  	       rdfs, NULL, NULL, NULL) == -1)
      return (1);
  return (0);
}

static int	new_client(t_socket serv, t_client *clients, int *actual)
{
  int		i;
  char		*buf;
  socklen_t	len;
  t_sockaddr	csin;

  len = sizeof(csin);
  if ((clients[*actual].sock = accept(serv, &csin, &len)) == -1)
    return (0);
  clients[*actual].ready = 0;
  i = 0;
  while (i < *actual)
    {
      write_socket(clients[i].sock, "new_cli");
      read_socket(clients[i].sock, &buf);
      i += 1;
    }
  *actual += 1;
  my_printf("\rWait for client %s[%d/%d]\033[0m",
	    (*actual != CLIENTS) ? "\033[31;1m" : "\033[32;1m",
	    *actual, CLIENTS);
  return (0);
}

static void	speak_client_w(t_client *clients, int *actual, fd_set *rdfs)
{
  char		*ret;
  int		len;
  int		i;

  i = 0;
  while (i < *actual)
    {
      if (FD_ISSET(clients[i].sock, rdfs))
	{
	  len = read_socket(clients[i].sock, &ret);
	  if (len == 0)
	    {
	      remove_client(clients, i, actual, 1);
	      my_printf("\rWait for client \033[31;1m[%d/%d]\033[0m",
			*actual, CLIENTS);
	    }
	  else
	    treat_resp_cli_w(clients, i, ret, *actual);
	}
      i += 1;
    }
}

static int	purge_standard(int actual)
{
  free(get_next_line(0));
  return (actual);
}

int		wait_connection_s(t_client *clients, t_socket sock)
{
  fd_set	rdfs;
  int		actual;
  int		stop;

  stop = 0;
  actual = 0;
  while (!stop)
    {
      set_select(&rdfs, clients, &actual, sock);
      if (FD_ISSET(STDIN_FILENO, &rdfs))
	stop = 2;
      else if (FD_ISSET(sock, &rdfs))
	stop = new_client(sock, clients, &actual);
      else
	speak_client_w(clients, &actual, &rdfs);
      if (actual == CLIENTS && check_cli_ready(clients, actual))
	{
	  broadcast_start(clients);
	  stop = 1;
	}
    }
  if (stop == 2)
    return (purge_standard(actual));
  return (-1);
}
