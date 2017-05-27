/*
** trear_resp_wait.c for treat_resp_wait in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 14:16:24 2017 Arthur Knoepflin
** Last update Fri May 26 01:45:55 2017 Arthur Knoepflin
*/

#include "server.h"
#include "my.h"

int	treat_resp_cli_w(t_client *clients,
			 int idx,
			 char *resp,
			 int actual)
{
  if (!my_strcmp(resp, "nb_cli_act"))
    write_socket(clients[idx].sock, my_int_to_char(actual));
  if (!my_strcmp(resp, "nb_cli_max"))
    write_socket(clients[idx].sock, my_int_to_char(CLIENTS));
  if (!my_strcmp(resp, "ready"))
    {
      clients[idx].ready = 1;
      write_socket(clients[idx].sock, "ok");
    }
}
