/*
** my_strcat.c for my_strcat in /home/nicolas.polomack/CPool_Day07
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Tue Oct 11 10:30:59 2016 Nicolas POLOMACK
** Last update Wed Nov 30 17:53:07 2016 Nicolas Polomack
*/

char	*my_strncat(char *dest, char *src, int size)
{
  int	iteration;
  int	i;
  int	c;

  c = 0;
  i = 0;
  iteration = 0;
  while (dest[i] != '\0' && iteration < size)
    {
      i += 1;
      iteration += 1;
    }
  iteration = 0;
  while (src[c] != '\0' && iteration < size)
    {
      dest[i] = src[c];
      c += 1;
      i += 1;
      iteration += 1;
    }
  dest[i] = '\0';
  return (dest);
}
