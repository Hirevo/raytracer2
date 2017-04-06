/*
** libs.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Fri Mar 31 20:08:30 2017 Nicolas Polomack
** Last update Thu Apr  6 16:58:15 2017 Cédric Thomas
*/

#include <dlfcn.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "my.h"
#include "raytracer.h"

int		my_filter(const struct dirent *dir)
{
  const char	*str = dir->d_name;

  if (dir->d_name[0] == '.')
    return (0);
  if (my_strncmp(str, "intersect_", 10) != 0)
    return (0);
  str += 10;
  while (*str && *str != '.')
    str += 1;
  if (*str == 0)
    return (0);
  return ((my_strcmp(str, ".so") == 0));
}

char	*catpath(char *str1, char *str2)
{
  char	*ret;

  if ((ret = malloc(my_strlen(str1) + my_strlen(str2) + 2)) == NULL)
    return (NULL);
  my_strcpy(ret, str1);
  my_strcat(ret, "/");
  my_strcat(ret, str2);
  return (ret);
}

int	alloc_lib_vars(t_params *params, int size)
{
  int	i;

  if ((params->libs = malloc(sizeof(*(params->libs)) * size)) == NULL ||
      (params->intersect = malloc(sizeof(*(params->intersect)) *
				  size)) == NULL ||
      (params->get_normal = malloc(sizeof(*(params->get_normal)) *
				   size)) == NULL ||
      (params->id = malloc(sizeof(int) * size)) == NULL)
    return (-1);
  i = -1;
  while (++i < size)
    params->id[i] = -1;
  return (0);
}

int		load_next_lib(t_params *params, struct dirent **dirs,
			      int i, int size)
{
  char		*name;
  char		**sym[2];
  int		id;

  if ((name = catpath("libs", dirs[i]->d_name)) == NULL)
    return (-1);
  if ((params->libs[i] = dlopen(name, RTLD_LAZY | RTLD_GLOBAL)) == NULL ||
      (sym[0] = dlsym(params->libs[i], "intersect")) == NULL ||
      (sym[1] = dlsym(params->libs[i], "normal")) == NULL ||
      (params->intersect[i] = dlsym(params->libs[i], *(sym[0]))) == NULL ||
      (params->get_normal[i] = dlsym(params->libs[i], *(sym[1]))) == NULL ||
      (id = *((int *)dlsym(params->libs[i], "id"))) == 0)
    return (-1 + 0 * my_printf("%s\n", dlerror()));
  if (id > size || params->id[id - 1] != -1)
    return (-1 + 0 * my_printf("%s: Bad id.\n", name));
  params->id[id - 1] = i;
  free(name);
  my_printf("Loaded '%s' with id %d\n", dirs[i]->d_name, id - 1);
  return (0);
}

int		load_libs(t_params *params)
{
  int		size;
  int		i;
  struct dirent	**dirs;

  if ((size = scandir("libs", &dirs, my_filter, alphasort)) == -1 ||
      alloc_lib_vars(params, size) == -1)
    return (-1);
  printf("%d\n", size);
  i = -1;
  while (++i < size)
    if (load_next_lib(params, dirs, i, size) == -1)
      return (-1);
  return (0);
}
