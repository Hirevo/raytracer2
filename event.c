/*
** event.c for raytracer2 in /home/nicolaspolomack/graphical/raytracer2
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Wed May 10 17:38:44 2017 Nicolas Polomack
** Last update Wed May 10 17:41:10 2017 Nicolas Polomack
*/

#include "raytracer.h"

void	check_keys(t_params *params)
{
  if (sfKeyboard_isKeyPressed(sfKeyZ))
    params->start.x += 10;
  if (sfKeyboard_isKeyPressed(sfKeyS))
    params->start.x -= 10;
  if (sfKeyboard_isKeyPressed(sfKeyQ))
    params->start.y += 10;
  if (sfKeyboard_isKeyPressed(sfKeyD))
    params->start.y -= 10;
  if (sfKeyboard_isKeyPressed(sfKeyLShift))
    params->start.z -= 10;
  if (sfKeyboard_isKeyPressed(sfKeySpace))
    params->start.z += 10;
  if (sfKeyboard_isKeyPressed(sfKeyUp))
    params->r.y += 3;
  if (sfKeyboard_isKeyPressed(sfKeyDown))
    params->r.y -= 3;
  if (sfKeyboard_isKeyPressed(sfKeyLeft))
    params->r.z += 3;
  if (sfKeyboard_isKeyPressed(sfKeyRight))
    params->r.z -= 3;
}
