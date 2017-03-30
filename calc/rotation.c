/*
** compense.c for raytracer in /home/nicolaspolomack/graphical/raytracer1
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Thu Feb  9 13:15:36 2017 Nicolas Polomack
** Last update Wed Mar 29 18:53:35 2017 Nicolas Polomack
*/

#include "sfcaster.h"
#include "raytracer.h"

void		rx(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.x = imp->x;
      tmp.y = imp->y * cosr(r) - imp->z * sinr(r);
      tmp.z = imp->y * sinr(r) + imp->z * cosr(r);
      *imp = tmp;
    }
}

void		ry(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.y = imp->y;
      tmp.x = imp->x * cosr(r) + imp->z * sinr(r);
      tmp.z = imp->z * cosr(r) - imp->x * sinr(r);
      *imp = tmp;
    }
}

void		rz(sfVector3f *imp, float r)
{
  sfVector3f	tmp;

  if (r)
    {
      tmp.z = imp->z;
      tmp.x = imp->x * cosr(r) - imp->y * sinr(r);
      tmp.y = imp->x * sinr(r) + imp->y * cosr(r);
      *imp = tmp;
    }
}

void	rotation(sfVector3f *restrict imp,
		 sfVector3f *restrict r)
{
  rx(imp, r->x);
  ry(imp, r->y);
  rz(imp, r->z);
}

void	anti_rotation(sfVector3f *restrict imp,
		      sfVector3f *restrict r)
{
  rx(imp, -r->x);
  ry(imp, -r->y);
  rz(imp, -r->z);
}
