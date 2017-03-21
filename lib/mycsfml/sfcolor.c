/*
** sfcolor.c for mycsfml in /home/nicolaspolomack/graphical/wireframe
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu@epitech.eu>
** 
** Started on  Sun Dec  4 21:06:41 2016 Nicolas Polomack
** Last update Sat Jan 14 17:17:06 2017 Nicolas Polomack
*/

#include <SFML/Graphics.h>

sfColor		get_sfcolor(int r, int g, int b, int a)
{
  sfColor	color;

  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  return (color);
}
