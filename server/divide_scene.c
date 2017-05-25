/*
** divide_scene.c for divide_scene.c in /home/Maxime/delivery/MUL/raytracer2/server/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Wed May 24 19:55:13 2017 Maxime Jenny
** Last update	Wed May 24 20:30:49 2017 Full Name
*/

int		divide_scene(t_server *server, sfVector2i *ss)
{
  int		i;

  i = 0;
  while (i < params->s.nb_clients)
    {
      server->clients[i].start.x = 0;
      server->clients[i].start.y = (ss->height / server->nb_clients) * i;
      server->clients[i].end.x = ss->width;
      server->clients[i].end.y = (ss->height / server->nb_clients) * (i + 1);
      server->clients[i].end.y += ((i == server->nb_clients - 1) ?
				   (ss->height % server->nb_clients) : (0));
      i++;
    }
}
