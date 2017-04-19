/*
** my_getnbr.c for my_getnbr in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed Apr 19 22:45:49 2017 Arthur Knoepflin
** Last update Wed Apr 19 22:49:00 2017 Arthur Knoepflin
*/

int	getnbr_parse(char *str)
{
  int	i;
  int	ret;
  int	neg;

  i = 0;
  neg = 0;
  ret = 0;
  while (str[i] && (str[i] == '-' || str[i] == '+'))
    {
      if (str[i] == '-')
	neg += 1;
      i += 1;
    }
  while (str[i])
    {
      ret *= 10;
      ret += str[i] - '0';
      i += 1;
    }
  if (neg % 2)
    return (-ret);
  else
    return (ret);
}
