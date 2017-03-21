/*
** my_strupcase.c for my_strupcase in /home/nicolas.polomack/CPool_Day06
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Mon Oct 10 12:10:37 2016 Nicolas POLOMACK
** Last update Tue Oct 11 12:14:52 2016 Nicolas POLOMACK
*/

char	*my_strcapitalize(char *str)
{
  int	count;

  count = 1;
  if (str[0] >= 97 && str[0] <= 122)
    str[0] = str[0] - 32;
  while (str[count] != '\0')
    {
      if (str[count] >= 'a' && str[count] <= 'z' &&
	  (str[count - 1] < 'A' || str[count - 1] > 'Z') &&
	  (str[count - 1] < 'a' || str[count - 1] > 'z') &&
	  (str[count - 1] < '0' || str[count - 1] > '9'))
        str[count] = str[count] - 32;
      else if ((str[count] >= 'A' && str[count] <= 'Z') &&
	       str[count - 1] != ' ')
	str[count] = str[count] + 32;
      count = count + 1;
    }
  return (str);
}
