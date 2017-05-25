/*
** my_strlen.c for my_strlen in /home/nicolas.polomack/CPool_Day04
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Thu Oct  6 10:41:18 2016 Nicolas POLOMACK
** Last update Thu May 25 10:07:10 2017 Arthur Knoepflin
*/

int	my_strlen(char *str)
{
  int	count;

  count = 0;
  while (str && str[count] != 0)
    count = count + 1;
  return (count);
}
