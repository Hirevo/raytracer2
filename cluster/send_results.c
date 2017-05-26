/*
** send_results.c for send in /home/Maxime/delivery/MUL/raytracer2/cluster/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu May 25 21:37:16 2017 Maxime Jenny
** Last update	Fri May 26 10:31:11 2017 Full Name
*/

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"
#include "my.h"
#include "socket_lib.h"
#include "sfcaster.h"

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

int		server_end(t_window *w, t_params *p, t_client *clients,
			   int serv)
{
  sfEvent	event;

  if (send_zones(clients, p))
    return (84);
  if ((gather_results(p, w, clients)) == -1)
    return (84);
  close_all(clients, CLIENTS);
  close(serv);
  if (!p->config.bmp)
    {
      create_window(&w->window, "Raytracer2", p->screen_size);
      sfTexture_updateFromPixels(w->texture, w->buffer->pixels,
				 w->buffer->width, w->buffer->height, 0, 0);
      sfRenderWindow_drawSprite(w->window, w->sprite, NULL);
      sfRenderWindow_display(w->window);
      while (!p->config.bmp && sfRenderWindow_isOpen(w->window))
	handle_events(w, p, &event);
    }
  save_buffers(w, p);
}
