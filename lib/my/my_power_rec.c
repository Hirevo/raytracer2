/*
** my_power_rec.c for my_power_rec in /home/nicolas.polomack/temp_CPool_Day05
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Fri Oct  7 11:01:28 2016 Nicolas POLOMACK
** Last update Mon Oct 10 10:22:32 2016 Nicolas POLOMACK
*/

int	my_power_rec(int nb, int p)
{
  int	resp_power_rec;

  resp_power_rec = 1;
  if (p == 0)
    {
      return (resp_power_rec);
    }
  else if (p < 0)
    {
      return (0);
    }
  else
    {
      resp_power_rec = nb;
      resp_power_rec = resp_power_rec * my_power_rec(nb, p - 1);
      return (resp_power_rec);
    }
}
