/*
** set_camera.c for set_camera in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu Apr 20 22:57:42 2017 Arthur Knoepflin
** Last update Wed May 24 10:17:13 2017 Arthur Knoepflin
*/

#include "raytracer.h"
#include "my.h"

static int	chk_born(sfVector2i *born, int mode)
{
  if (mode == 0)
    {
      born->x = -1;
      born->y = -1;
      return (0);
    }
  else if (mode == 1)
    {
      if (born->x == -1 || born->y == -1)
	return (1);
      return (0);
    }
}

static char	*get_cam_cfg(char **file)
{
  int		i;
  int		j;
  sfVector2i	born;

  i = 0;
  chk_born(&born, 0);
  while (file[i])
    {
      j = 0;
      while (file[i][j])
	{
	  if (!my_strncmp(file[i] + j, CAMERA, my_strlen(CAMERA)))
	    {
	      born.x = j;
	      born.y = i;
	    }
	  j += 1;
	}
      i += 1;
    }
  if (chk_born(&born, 1))
    return (NULL);
  return (extract_str_from_born(file, born));
}

void	init_pos_rot(t_params *param)
{
  param->start.x = 0;
  param->start.y = 0;
  param->start.z = 0;
  param->r.x = 0;
  param->r.y = 0;
  param->r.z = 0;
}

void	set_camera(t_params *param, char **file)
{
  char	*cfg;
  int	i;

  i = 0;
  init_pos_rot(param);
  if ((cfg = get_cam_cfg(file)) == NULL)
    return ;
  while (cfg[i])
    {
      if (!my_strncmp(cfg + i, POS_N, my_strlen(POS_N)))
	param->start = get_pos_from_node(cfg + i, POS_N);
      if (!my_strncmp(cfg + i, ROT_N, my_strlen(ROT_N)))
	param->r = get_pos_from_node(cfg + i, ROT_N);
      i += 1;
    }
}
