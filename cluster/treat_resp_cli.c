/*
** treat_resp_cli.c for treat_resp_cli in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 18:31:53 2017 Arthur Knoepflin
** Last update Fri May 26 11:11:49 2017 Arthur Knoepflin
*/

#include <stdlib.h>
#include "server.h"
#include "my.h"

int	treat_resp(t_socket sock, char *input)
{
  write_socket(sock, "ok");
  if (!my_strcmp(input, "new_cli"))
    print_state_wait(sock);
  else if (!my_strcmp(input, "rm_cli"))
    print_state_wait(sock);
  else if (!my_strcmp(input, "start"))
    {
      my_printf("\nStart !!\n");
      return (1);
    }
  else
    my_printf("The server said : %s\n", input);
  free(input);
  return (0);
}
