/*
** time.c for time in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Tue May 23 09:22:15 2017 Arthur Knoepflin
** Last update Sun May 28 18:24:25 2017 Arthur Knoepflin
*/

#include <sys/time.h>
#include <stdlib.h>
#include "raytracer.h"
#include "my.h"

unsigned long long	get_time()
{
  struct timeval	te;
  unsigned long long	ms;

  gettimeofday(&te, NULL);
  ms = te.tv_sec * 1000LL + te.tv_usec / 1000;
  return (ms);
}

static char	*time_to_char(int nb)
{
  char		*ret;

  if (nb < 0 || nb >= 100)
    return (NULL);
  if ((ret = malloc(sizeof(char) * 3)) == NULL)
    return (NULL);
  ret[2] = '\0';
  ret[0] = (nb / 10) + '0';
  ret[1] = (nb % 10) + '0';
  return (ret);
}

static char	*transform_sec(int t_sec)
{
  char		*c_sec;
  char		*c_min;
  char		*c_hour;
  int		time[3];
  char		*ret;

  time[0] = -1;
  time[1] = t_sec / 60;
  time[2] = t_sec % 60;
  if (time[1] > 60)
    {
      time[0] = time[1] / 60;
      time[1] = time[1] % 60;
    }
  if ((c_sec = time_to_char(time[2])) == NULL)
    return (NULL);
  if ((c_min = time_to_char(time[1])) == NULL)
    return (NULL);
  ret = my_fstrcat(c_min, ":", 1);
  if (time[0] == -1)
    return (my_fstrcat(ret, c_sec, 2));
  if ((c_hour = time_to_char(time[0])) == NULL)
    return (NULL);
  ret = my_fstrcat(":", my_fstrcat(ret, c_sec, 2), 3);
  return (my_fstrcat(c_hour, ret, 2));
}

char			*get_time_calc(t_window *w,
				       char *percent)
{
  float			dif_time;
  float			total;
  int			sec;
  unsigned long long	time;
  char			*c_time;
  char			*ret;

  time = get_time() - w->time_start;
  dif_time = time / 1000.0;
  total = (dif_time * 100.0) / w->progress;
  sec = (int) (total - (dif_time - 0.999));
  if ((c_time = transform_sec(sec)) == NULL)
    return (my_fstrcat(percent,
		       "% - Plus de 100 minutes restantes", 1));
  ret = my_fstrcat(percent, "% - ", 1);
  return (my_fstrcat(ret, c_time, 2));
}
