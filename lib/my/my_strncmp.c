/*
** my_strncmp.c for my_strncmp in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 09:38:55 2016 Nicolas POLOMACK
** Last update Tue Mar 28 19:07:36 2017 Nicolas Polomack
*/

int	my_strncmp(char *str1, char *str2, int n)
{
  int	i;

  i = 0;
  while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
    i += 1;
  return (str2[i] - str1[i]);
}
