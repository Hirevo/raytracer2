/*
** recv_parse.c for recv_parse in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 22:30:45 2017 Arthur Knoepflin
** Last update Thu May 25 18:35:21 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

static void	long_recv(t_socket sock, t_params *p, int i, int len)
{
  int		j;

  j = 0;
  while (j < len)
    {
      j += recv(sock, p->objs[i].buffer->pixels + j,
		len - j, 0);
    }
  send(sock, "ok", 2, 0);
}

static int	send_buffer(t_socket sock,
			    t_params *p,
			    int i)
{
  if ((p->objs[i].buffer = malloc(sizeof(t_my_framebuffer))) == NULL)
    return (1);
  recv(sock, p->objs[i].buffer, sizeof(t_my_framebuffer), 0);
  if ((p->objs[i].buffer->pixels =
       malloc(sizeof(sfUint8) * p->objs[i].buffer->width *
	      p->objs[i].buffer->height * 4)) == NULL)
    return (1);
  long_recv(sock, p, i,
	    sizeof(sfUint8) * p->objs[i].buffer->width *
	    p->objs[i].buffer->height * 4);
  return (0);
}

static int	recv_obj_2(t_socket sock,
			   t_params *p,
			   int i,
			   sfVector3f **ptr)
{
  int		j;

  if ((*ptr = malloc(sizeof(sfVector3f) *
		     p->objs[i].obj_parse->nb_poly)) == NULL)
    return (1);
  j = 0;
  while (j < sizeof(sfVector3f) *
  	 p->objs[i].obj_parse->nb_poly)
    {
      j += recv(sock, (*ptr) + j, sizeof(sfVector3f) *
		p->objs[i].obj_parse->nb_poly - j, 0);
    }
  send(sock, "ok", 2, 0);
  return (0);
}

static int	recv_obj(t_socket sock, t_params *p)
{
  int		i;

  i = 0;
  while (i < p->nb_objs)
    {
      if (p->objs[i].obj_parse)
      	{
      	  if ((p->objs[i].obj_parse = malloc(sizeof(t_obj_file))) == NULL)
      	    return (1);
      	  recv(sock, p->objs[i].obj_parse, sizeof(t_obj_file), 0);
      	  if (recv_obj_2(sock, p, i, &p->objs[i].obj_parse->p1) ||
      	      recv_obj_2(sock, p, i, &p->objs[i].obj_parse->p2) ||
      	      recv_obj_2(sock, p, i, &p->objs[i].obj_parse->p3))
      	    return (1);
      	}
      p->objs[i].file = NULL;
      if (p->objs[i].buffer)
      	{
      	  if (send_buffer(sock, p, i))
      	    return (1);
      	}
      i += 1;
    }
  return (0);
}

int		recv_parse(t_socket sock, t_params *p)
{
  t_light	*lights;
  char		*buf;

  recv(sock, p, sizeof(t_params), 0);
  if ((lights = malloc(sizeof(t_light) * p->nb_lights)) == NULL)
    return (1);
  recv(sock, lights, p->nb_lights * sizeof(t_light), 0);
  p->lights = lights;
  if ((p->objs = malloc(p->nb_objs * sizeof(t_obj))) == NULL)
    return (1);
  recv(sock, p->objs, p->nb_objs * sizeof(t_obj), 0);
  if (recv_obj(sock, p))
    return (1);
  if (load_libs(p) == -1)
    return (1);
  send(sock, "ready", 5, 0);
  return (0);
}
