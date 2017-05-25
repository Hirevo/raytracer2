/*
** send_parse.c for send_parse in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 21:39:29 2017 Arthur Knoepflin
** Last update Thu May 25 14:17:27 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

static int	send_obj_ptr(t_socket sock, t_params *p)
{
  int		i;

  i = 0;
  while (i < p->nb_objs)
    {
      if (p->objs[i].obj_parse)
	{
	  send(sock, p->objs[i].obj_parse, sizeof(t_obj_file), 0);
	  send(sock, p->objs[i].obj_parse->p1,
	       sizeof(sfVector3f) * p->objs[i].obj_parse->nb_poly, 0);
	  send(sock, p->objs[i].obj_parse->p2,
	       sizeof(sfVector3f) * p->objs[i].obj_parse->nb_poly, 0);
	  send(sock, p->objs[i].obj_parse->p3,
	       sizeof(sfVector3f) * p->objs[i].obj_parse->nb_poly, 0);
	}
      if (p->objs[i].buffer)
	{
	  send(sock, p->objs[i].buffer, sizeof(t_my_framebuffer), 0);
	  send(sock, p->objs[i].buffer->pixels, sizeof(sfUint8) *
	       p->objs[i].buffer->width * p->objs[i].buffer->height * 4, 0);
	}
      i += 1;
    }
}

static int	send_for_cli(t_socket sock, t_params *p)
{
  send(sock, p, sizeof(t_params), 0);
  send(sock, p->lights, p->nb_lights * sizeof(t_light) , 0);
  send(sock, p->objs, p->nb_objs * sizeof(t_obj), 0);
  send_obj_ptr(sock, p);
}

int	send_parse(t_client *clients, t_params *p)
{
  int	i;

  i = 0;
  while (i < CLIENTS)
    {
      send_for_cli(clients[i].sock, p);
      i += 1;
    }
}
