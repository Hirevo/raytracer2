/*
** my_getfloat.c for my_getfloat in /home/arthur/delivery/CPE/CPE_2016_n4s
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Thu May  4 09:41:02 2017 Arthur Knoepflin
** Last update Tue May  9 23:22:56 2017 Arthur Knoepflin
*/

static int	my_getfloat_core(char *str, int i, long long *ret, int *dot_pos)
{
  int		nb_dot;

  nb_dot = 0;
  while (str[i] && ((str[i] >= '0' && str[i] <= '9') ||
		    str[i] == '.') && nb_dot <= 1)
    {
      if (str[i] == '.')
	nb_dot += 1;
      if (str[i] == '.' && nb_dot <= 1)
	*dot_pos = i;
      if (str[i] != '.')
	{
	  *ret *= 10.0;
	  *ret += str[i] - '0';
	}
      i += 1;
    }
  return (i);
}

static int	is_dot(char *str, int i)
{
  int		nb_dot;

  nb_dot = 0;
  while (str[i] && ((str[i] >= '0' && str[i] <= '9') ||
		    str[i] == '.') && nb_dot <= 1)
    {
      if (str[i] == '.')
	nb_dot += 1;
      i += 1;
    }
  return (nb_dot);
}

static int	my_power(int nb)
{
  int		i;
  int		ret;

  i = 0;
  ret = 1;
  while (i < nb)
    {
      ret *= 10;
      i += 1;
    }
  return (ret);
}

float		my_getfloat(char *str)
{
  int		end;
  int		neg;
  int		dot_pos;
  long long	nb;
  float		ret;
  int		i;

  i = 0;
  neg = 0;
  nb = 0;
  while (str[i] && (str[i] == '-' || str[i] == '+'))
    {
      if (str[i] == '-')
	neg = !neg;
      i += 1;
    }
  end = my_getfloat_core(str, i, &nb, &dot_pos);
  if (is_dot(str, i))
    ret = (float) nb / (float) my_power(end - dot_pos - 1);
  if (neg)
    return (-ret);
  return (ret);
}
