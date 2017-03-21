/*
** my_strlen.c for my_strlen in /home/nicolas.polomack/CPool_Day04
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Thu Oct  6 10:41:18 2016 Nicolas POLOMACK
** Last update Fri Nov  4 12:09:48 2016 Nicolas POLOMACK
*/

int	my_strlen(char *str)
{
  int	count;

  count = 0;
  while (str[count] != 0)
    count = count + 1;
  return (count);
}
