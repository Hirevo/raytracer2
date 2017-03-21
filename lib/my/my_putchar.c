/*
** my_putchar.c for my_putchar in /home/nicolas.polomack/libraries/lib_backup
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Fri Oct 14 10:44:55 2016 Nicolas POLOMACK
** Last update Thu Jan  5 16:39:06 2017 Nicolas Polomack
*/

#include <unistd.h>

void	my_putchar_printf(char c, int *count)
{
  *count += 1;
  write(1, &c , 1);
}

void	my_putchar_fd(char c, int fd)
{
  write(fd, &c, 1);
}

void	my_putchar(char c)
{
  write(1, &c , 1);
}
