/*
** get_ip.c for get_ip in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 22:12:58 2017 Arthur Knoepflin
** Last update Thu May 25 10:09:39 2017 Arthur Knoepflin
*/

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

char			*get_ip()
{
  struct ifaddrs	*ifa;
  int			family;
  int			s;
  char			host[NI_MAXHOST];

  if (getifaddrs(&ifa) == -1)
    return (NULL);
  while (ifa)
    {
      if (ifa->ifa_addr)
	{
	  s = getnameinfo(ifa->ifa_addr,
			  sizeof(struct sockaddr_in),
			  host, NI_MAXHOST, NULL, 0,
			  NI_NUMERICHOST);
	}
      if ((my_strcmp(ifa->ifa_name, "wlp2s0") == 0) &&
	  (ifa->ifa_addr->sa_family == AF_INET))
	return (my_strdup(host));
      ifa = ifa->ifa_next;
    }
  return (NULL);
}
