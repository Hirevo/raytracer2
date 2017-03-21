/*
** get_next_line.c for get_next_line in /home/nicolaspolomack/cpe/CPE_2016_getnextline
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Mon Jan  2 12:59:49 2017 Nicolas Polomack
** Last update Thu Feb  2 18:25:37 2017 Nicolas Polomack
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*line_cases(int fd, int *fd_s, char **final)
{
  int	i;

  i = get_line_str(fd, final, READ_SIZE);
  if (i > 0)
    return (get_final_line(final));
  else if (**final != 0)
    {
      *fd_s = -1;
      return (*final);
    }
  else
    {
      free(*final);
      *final = NULL;
      return (NULL);
    }
}

char	*my_realloc(char *buffer, char *overflow)
{
  int	i;
  int	j;
  char	*temp;

  i = -1;
  j = -1;
  while (overflow[++i]);
  while (buffer[++j]);
  if ((temp = malloc(i + j + 1)) == NULL)
    return (NULL);
  i = -1;
  j = 0;
  while (overflow[++i] != 0)
    temp[i] = overflow[i];
  while (buffer[j] != 0)
    temp[i++] = buffer[j++];
  temp[i] = 0;
  free(overflow);
  return (temp);
}

int	get_line_str(const int fd, char **final, int size)
{
  char	buffer[size + 1];
  int	chars;

  chars = -1;
  while ((*final)[++chars] != 0)
    if ((*final)[chars] == 10)
      return (2);
  chars = 1;
  while ((chars = read(fd, buffer, READ_SIZE)) > 0)
    {
      buffer[chars] = 0;
      if ((*final = my_realloc(buffer, *final)) == NULL)
	return (-1);
      chars = 0;
      while ((*final)[chars] != 0)
	{
	  if ((*final)[chars] == 10)
	    return (1);
	  chars += 1;
	}
      chars = 1;
    }
  return (0);
}

char	*get_final_line(char **overflow)
{
  char	*final;
  int	i;
  int	j;

  i = -1;
  j = 0;
  while ((*overflow)[++i] != 10);
  if ((final = malloc(i + 1)) == NULL)
    return (NULL);
  i = -1;
  while ((*overflow)[++i] != 10 && (*overflow)[i] != 0)
    final[i] = (*overflow)[i];
  final[i] = 0;
  if ((*overflow)[i] == 0)
    return (final);
  while ((*overflow)[++i] != 0)
    {
      (*overflow)[j++] = (*overflow)[i];
      (*overflow)[i] = 0;
    }
  while ((*overflow)[j] != 0)
    (*overflow)[j++] = 0;
  return (final);
}

char		*get_next_line(const int fd)
{
  static char	*final = NULL;
  static int	fd_s = -1;

  if (READ_SIZE <= 0)
    return (NULL);
  if (final == NULL || (fd_s != fd && fd_s == -1))
    {
      fd_s = fd;
      if ((final = malloc(1)) == NULL)
	return (NULL);
      *final = 0;
    }
  return (line_cases(fd, &fd_s, &final));
}
