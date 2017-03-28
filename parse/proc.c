/*
** proc.c for raytracer in /home/nicolaspolomack/graphical/raytracer1/multithread
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Feb 13 09:31:24 2017 Nicolas Polomack
** Last update Mon Feb 13 09:39:44 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include "my.h"
#include "get_next_line.h"

int	get_core_count()
{
  int	fd;
  int	cores;
  char	*line;

  if ((fd = open("/proc/cpuinfo", O_RDONLY)) == -1)
    return (-1);
  cores = 0;
  while ((line = get_next_line(fd)))
    {
      if (my_strstr(line, "processor"))
	cores += 1;
      free(line);
    }
  close(fd);
  return (cores);
}
