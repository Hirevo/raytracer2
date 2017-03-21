/*
** my_putstr_fd.c for libmy in 
** 
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
** 
** Started on  Thu Jan  5 16:18:27 2017 Nicolas Polomack
** Last update Thu Jan  5 16:20:11 2017 Nicolas Polomack
*/

void	my_putstr_fd(char *str, int fd)
{
  int	i;

  i = -1;
  while (str[++i] != 0)
    my_putchar(str[i], fd);
}
