/*
** focal.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Mar 29 16:44:06 2017 Nicolas Polomack
** Last update Wed Mar 29 19:22:20 2017 Nicolas Polomack
*/

void	set_focal_dist(t_thread *t)
{
  int	i;
  float	dist;
  float	temp;

  t->ray.dir = calc_dir_vector(t->params->screen_size,
			       t->params->screen_size.x / 2,
			       t->params->screen_size.y / 2,
			       104);
  rotation(&t->ray.dir, &t->params->r);
  i = -1;
  t->focal_dist = FLT_MAX;
  while (++i < t->params->nb_objs)
    {
      temp = gather_dist(t, i);
      if (temp >= 0 && (t->focal_dist == -1 ||
			temp < t->focal_dist))
	t->focal_dist = temp;
    }
}