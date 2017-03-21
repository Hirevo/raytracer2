/*
** my_strcmp.c for my_strcmp in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 09:38:55 2016 Nicolas POLOMACK
** Last update Sun Jan 15 23:20:27 2017 Nicolas Polomack
*/

int	my_strcmp(char *str1, char *str2)
{
  int	i;

  i = 0;
  while (str1[i] && str2[i] && str1[i] == str2[i])
    i += 1;
  return (str1[i] - str2[i]);
}
