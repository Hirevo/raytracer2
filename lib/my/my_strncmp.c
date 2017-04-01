/*
** my_strncmp.c for my_strncmp in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 09:38:55 2016 Nicolas POLOMACK
** Last update Sat Apr  1 02:35:47 2017 Nicolas Polomack
*/

int	my_strncmp(const char *str1, const char *str2, int n)
{
  int	i;

  i = 0;
  while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
    i += 1;
  if (i == n)
    return (0);
  return (str2[i] - str1[i]);
}
