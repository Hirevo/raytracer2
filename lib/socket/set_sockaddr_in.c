/*
** set_sockaddr_in.c for set_it in /home/Maxime/perso/echat/lib/socket/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Tue May  2 19:03:13 2017 Maxime Jenny
** Last update	Sat May 27 21:20:59 2017 Full Name
*/

#include <socket_lib.h>

void		set_sockaddr_in(t_SOCKADDR_IN *son)
{
  son->sin_addr.s_addr = htonl(INADDR_ANY);
  son->sin_family = AF_INET;
  son->sin_port = htons(PORTY);
}
