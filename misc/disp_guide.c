/*
** check.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Feb  9 02:34:59 2017 Nicolas Polomack
** Last update Sat Apr  1 04:50:37 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include "get_next_line.h"
#include "raytracer.h"
#include "my.h"

int	disp_guide()
{
  int	fd;
  char	*line;

  if ((fd = open("help.txt", O_RDONLY)) == -1)
    return (84);
  while ((line = get_next_line(fd)))
    {
      my_printf("%s\n", line);
      free(line);
    }
  close(fd);
  return (0);
}
