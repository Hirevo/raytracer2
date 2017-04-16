/*
** get_file.c for get_parse in /home/arthur/delivery/MUL/raytracer2
** 
** Made by 
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 13 18:26:50 2017 
** Last update Thu Apr 13 22:39:14 2017 
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "raytracer.h"
#include "my.h"

static int	open_file(char *path)
{
  int		fd;

  if ((fd = open(path, O_RDONLY)) == -1)
    my_puterror("Le fichier de scene n'existe pas\n");
  return (fd);
}

char	**realloc_tab(char **file, int *size)
{
  int	i;
  char	**tmp;

  if ((tmp = malloc(sizeof(char *) * (*size + SIZE_BUF))) == NULL)
    return (NULL);
  i = 0;
  while (i < *size)
    {
      tmp[i] = my_strdup(file[i]);
      free(file[i]);
      i += 1;
    }
  free(file);
  *size += SIZE_BUF;
  return (tmp);
}

char	**get_file(char *file)
{
  int	i;
  int	fd;
  int	size;
  char	*tmp;
  char	**ret;

  if ((fd = open_file(file)) == -1)
    return (NULL);
  if ((ret = malloc(sizeof(char *) * (SIZE_BUF))) == NULL)
    return (NULL);
  size = SIZE_BUF;
  i = 0;
  while ((tmp = get_next_line(fd)))
    {
      ret[i] = my_strdup(tmp);
      free(tmp);
      i += 1;
      if (i >= size)
	if ((ret = realloc_tab(ret, &size)) == NULL)
	  return (NULL);
    }
  ret[i] = NULL;
  close(fd);
  return (ret);
}
