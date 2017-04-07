/*
** sfcreator.c for mycsfml in /home/nicolaspolomack/graphical/wolf3d
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Sat Dec 24 00:06:29 2016 Nicolas Polomack
** Last update Wed Apr  5 17:24:37 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <SFML/Graphics.h>

sfVector2f	*create_vector2f(float x, float y)
{
  sfVector2f	*v;

  if ((v = malloc(sizeof(sfVector2f))) == NULL)
    return (NULL);
  v->x = x;
  v->y = y;
  return (v);
}

sfVector3f	*create_vector3f(float x, float y, float z)
{
  sfVector3f	*v;

  if ((v = malloc(sizeof(sfVector3f))) == NULL)
    return (NULL);
  v->x = x;
  v->y = y;
  v->z = z;
  return (v);
}

sfVector3f	v3f(float x, float y, float z)
{
  sfVector3f	v;

  v.x = x;
  v.y = y;
  v.z = z;
  return (v);
}

sfVector2f	v2f(float x, float y)
{
  sfVector2f	v;

  v.x = x;
  v.y = y;
  return (v);
}

sfVector2i	*create_vector2i(int x, int y)
{
  sfVector2i	*v;

  if ((v = malloc(sizeof(sfVector2i))) == NULL)
    return (NULL);
  v->x = x;
  v->y = y;
  return (v);
}
