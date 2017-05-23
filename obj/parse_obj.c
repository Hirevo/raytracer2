/*
** parse_obj.c for parse_obj in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May  9 22:05:59 2017 Arthur Knoepflin
** Last update Tue May 23 22:02:56 2017 Arthur Knoepflin
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "raytracer.h"
#include "my.h"

int	open_file(char *path)
{
  int	fd;

  if ((fd = open(path, O_RDONLY)) == -1)
    my_puterror("Impossible to load obj file\n");
  return (fd);
}

static char	**realloc_file(char **ret, int *max)
{
  char		**new;
  int		i;

  if ((new = malloc(sizeof(char *) * (*max + SIZE_BUF))) == NULL)
    return (NULL);
  i = 0;
  while (i < *max)
    {
      new[i] = my_strdup(ret[i]);
      free(ret[i]);
      i += 1;
    }
  free(ret);
  *max += SIZE_BUF;
  return (new);
}

static char	**load_file(char *path)
{
  char		**ret;
  char		*tmp;
  int		max;
  int		i;
  int		fd;

  if ((fd = open_file(path)) == -1)
    return (NULL);
  if ((ret = malloc(sizeof(char *) * SIZE_BUF)) == NULL)
    return (NULL);
  max = SIZE_BUF;
  i = 0;
  while ((tmp = get_next_line(fd)))
    {
      ret[i] = my_strdup(tmp);
      free(tmp);
      i += 1;
      if (i >= max)
	{
	  if ((ret = realloc_file(ret, &max)) == NULL)
	    return (NULL);
	}
    }
  ret[i] = NULL;
  close(fd);
  return (ret);
}

t_obj_file	*parse_obj_file(char *path)
{
  t_obj_file	*ret;
  sfVector3f	*pos;
  char		**file;

  if (path == NULL)
    return (NULL);
  if ((ret = malloc(sizeof(t_obj_file))) == NULL)
    return (NULL);
  if ((file = load_file(path)) == NULL)
    return (NULL);
  ret->nb_vert = nb_vert(file);
  ret->nb_poly = get_nb_poly(file);
  printf("Vertex : %d || Polygon : %d\n", ret->nb_vert, ret->nb_poly);
  if ((pos = parse_pos_vert(file, ret)) == NULL)
    return (NULL);
  if ((ret->p1 = malloc(sizeof(sfVector3f) * ret->nb_poly)) == NULL ||
      (ret->p2 = malloc(sizeof(sfVector3f) * ret->nb_poly)) == NULL ||
      (ret->p3 = malloc(sizeof(sfVector3f) * ret->nb_poly)) == NULL)
    return (NULL);
  parse_poly(file, pos, ret);
  return (ret);
}
