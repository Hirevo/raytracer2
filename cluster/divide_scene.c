/*
** divide_scene.c for divide_scene.c in /home/Maxime/delivery/MUL/raytracer2/server/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Wed May 24 19:55:13 2017 Maxime Jenny
** Last update	Thu May 25 12:05:37 2017 Full Name
*/

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "raytracer.h"
#include "server.h"

int		divide_scene(t_client *clients, sfVector2i *ss, int nb_clients)
{
  int		i;

  i = 0;
  if (clients == NULL || ss == NULL)
    return (-1);
  while (i < nb_clients)
    {
      clients[i].zone.s_x = 0;
      clients[i].zone.s_y = (ss->y / nb_clients) * i;
      clients[i].zone.e_x = ss->x;
      clients[i].zone.e_y = (ss->y / nb_clients) * (i + 1);
      clients[i].zone.e_y += ((i == nb_clients - 1) ?
				(ss->y % nb_clients) : (0));
      i++;
    }
  return (0);
}
