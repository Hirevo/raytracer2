/*
** my_strupcase.c for my_strupcase in /home/nicolas.polomack/CPool_Day06
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Mon Oct 10 12:10:37 2016 Nicolas POLOMACK
** Last update Mon Nov 28 18:56:27 2016 Nicolas Polomack
*/

char	*my_strlowcase(char *str)
{
  int	count;

  count = -1;
  while (str[++count] != 0)
    if (str[count] >= 'A' && str[count] <= 'Z')
      str[count] = str[count] + 32;
  return (str);
}
