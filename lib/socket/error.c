/*
** error.c for error in /home/Maxime/perso/echat/lib/socket/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Thu May  4 20:29:27 2017 Maxime Jenny
** Last update	Thu May 25 11:37:23 2017 Full Name
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "my.h"

int		my_put_error(char *str, int nbr)
{
  perror(str);
  return (nbr);
}
