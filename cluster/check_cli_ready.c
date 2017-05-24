/*
** check_cli_ready.c for check_cli_ready in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 20:34:09 2017 Arthur Knoepflin
** Last update Wed May 24 20:37:30 2017 Arthur Knoepflin
*/

#include "server.h"

int	check_cli_ready(t_client *clients, int cli)
{
  int	i;

  i = 0;
  while (i < cli)
    {
      if (clients[i].ready == 0)
	return (0);
      i += 1;
    }
  return (1);
}
