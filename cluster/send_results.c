/*
** send_results.c for send in /home/Maxime/delivery/MUL/raytracer2/cluster/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu May 25 21:37:16 2017 Maxime Jenny
** Last update	Thu May 25 22:24:49 2017 Full Name
*/

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "sfcaster.h"
#include "my.h"

void	send_results(int socket, t_window *w, t_zone *s)
{
  char	buffer[7];

  recv(socket, buffer, 7, 0);
  if (my_strcmp(buffer, "RESULT"))
    my_printf("KO !\n");
  send(socket, &(w->buffer->pixels[((s->s_y *
				     w->buffer->width) + s->s_x) * 4]),
       (s->e_x - s->s_x) * (s->e_y - s->s_y) * 4, 0);
}
