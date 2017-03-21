/*
** my_strncpy.c for my_strncpy in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 09:22:36 2016 Nicolas POLOMACK
** Last update Thu Jan  5 01:40:29 2017 Nicolas Polomack
*/

char	*my_strncpy(char *dest, char *src, int n)
{
  int	count;

  count = 0;
  while (n > 0)
    {
      dest[count] = src[count];
      count = count + 1;
      n = n - 1;
    }
  dest[count] = 0;
  return (dest);
}
