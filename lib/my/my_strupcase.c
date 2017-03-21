/*
** my_strupcase.c for my_strupcase in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 12:10:37 2016 Nicolas POLOMACK
** Last update Tue Oct 11 17:20:22 2016 Nicolas POLOMACK
*/

char	*my_strupcase(char *str)
{
  int	count;

  count = 0;
  while (str[count] != '\0')
    {
      if (str[count] >= 97 && str[count] <= 122)
	str[count] = str[count] - 32;
      count = count + 1;
    }
  return (str);
}
