/*
** send_parse.c for send_parse in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 21:39:29 2017 Arthur Knoepflin
** Last update Thu May 25 17:50:11 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"
#include "my.h"

static int	send_obj_ptr(t_socket sock, t_params *p)
{
  char		buf[2];
  int		i;

  i = 0;
  while (i < p->nb_objs)
    {
      if (p->objs[i].obj_parse)
      	{
      	  send(sock, p->objs[i].obj_parse, sizeof(t_obj_file), 0);
      	  /* send(sock, p->objs[i].obj_parse->p1, */
      	  /*      sizeof(sfVector3f) * p->objs[i].obj_parse->nb_poly, 0); */
      	  /* send(sock, p->objs[i].obj_parse->p2, */
      	  /*      sizeof(sfVector3f) * p->objs[i].obj_parse->nb_poly, 0); */
      	  /* send(sock, p->objs[i].obj_parse->p3, */
      	  /*      sizeof(sfVector3f) * p->objs[i].obj_parse->nb_poly, 0); */
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
  char		sig[6];

  send(sock, p, sizeof(t_params), 0);
  send(sock, p->lights, p->nb_lights * sizeof(t_light) , 0);
  send(sock, p->objs, p->nb_objs * sizeof(t_obj), 0);
  send_obj_ptr(sock, p);
  recv(sock, sig, 5, 0);
  sig[5] = '\0';
  if (!my_strcmp(sig, "ready"))
    return (0);
  return (1);
}

int	send_parse(t_client *clients, t_params *p)
{
  int	i;

  i = 0;
  while (i < CLIENTS)
    {
      if (send_for_cli(clients[i].sock, p))
	return (1);
      i += 1;
    }
  return (0);
}
