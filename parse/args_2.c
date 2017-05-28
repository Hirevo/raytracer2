/*
** args_2.c for args_2 in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Sun May 28 12:18:58 2017 Arthur Knoepflin
** Last update Sun May 28 12:20:32 2017 Arthur Knoepflin
*/

int	get_index(char *flags, char arg)
{
  int	i;

  i = 0;
  while (flags[i])
    {
      if (flags[i] == arg)
	return (i);
      i += 1;
    }
  return (-1);
}
