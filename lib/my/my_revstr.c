/*
** my_revstr.c for my_revstr in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 09:30:02 2016 Nicolas POLOMACK
** Last update Tue Oct 11 20:48:27 2016 Nicolas POLOMACK
*/

int	my_strlen(char *str)
{
  int	count;

  count = 0;
  while (*str != '\0')
    {
      count = count + 1;
      str = str + 1;
    }
  return (count);
}

char	*my_revstr(char *str)
{
  char	buffer;
  int	count;
  int	reverse_count;

  count = 0;
  reverse_count = my_strlen(str) - 1;
  while (reverse_count >= 0)
    {
      buffer = *(str + count);
      *(str + count) = *(str - reverse_count);
      *(str - reverse_count) = buffer;
      reverse_count = reverse_count - 1;
      count = count + 1;
    }
  return (str);
}
