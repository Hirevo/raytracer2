/*
** my_mset.c for my_mset in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur@epitech.net>
** 
** Started on  Tue Apr 18 21:53:52 2017 Arthur Knoepflin
** Last update Tue Apr 18 21:56:43 2017 Arthur Knoepflin
*/

void	my_mset(void *str, int c, int len)
{
  int	i;

  i = 0;
  while (i < len)
    {
      ((char *) str)[i] = c;
      i += 1;
    }
}
