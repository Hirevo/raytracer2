/*
** help.c for raytracer2 in 
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Apr  7 16:46:51 2017 Nicolas Polomack
** Last update Fri Apr  7 16:52:04 2017 Nicolas Polomack
*/

#include "get_next_line.h"
#include "my_printf.h"

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
