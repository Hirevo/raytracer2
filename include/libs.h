/*
** libs.h for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed Apr  5 17:36:47 2017 Nicolas Polomack
** Last update Thu May 25 21:16:46 2017 Nicolas Polomack
*/

#ifndef LIBS_H_
# define LIBS_H_

# include "raytracer.h"

/*
** intersect_sphere.c
*/
float	intersect_sphere(sfVector3f, sfVector3f, t_obj *);
float	intersect_plane(sfVector3f, sfVector3f, t_obj *);
float	intersect_limited_plane(sfVector3f, sfVector3f, t_obj *);
float	intersect_cyl(sfVector3f, sfVector3f, t_obj *);
float	intersect_closed_cyl(sfVector3f, sfVector3f, t_obj *);
float	intersect_cone(sfVector3f, sfVector3f, t_obj *);
float	intersect_semi_cone(sfVector3f, sfVector3f, t_obj *);
float	intersect_closed_cone(sfVector3f, sfVector3f, t_obj *);
float	intersect_disk(sfVector3f, sfVector3f, t_obj *);
float	intersect_triangle(sfVector3f, sfVector3f, t_obj *);
float	intersect_cube(sfVector3f, sfVector3f, t_obj *);

#endif /* !LIBS_H_ */
