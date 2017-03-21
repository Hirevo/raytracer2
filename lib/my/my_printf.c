/*
** my_printf.c for my_printf in /home/nicolas/psu/PSU_2016_my_printf/
**
** Made by Nicolas Polomack
** Login   <nicolas.polomack@epitech.eu>
**
** Started on  Wed Nov  9 09:21:53 2016 Nicolas Polomack
** Last update Thu Feb  2 00:28:39 2017 Nicolas Polomack
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "my.h"

void	my_octal_putstr(char *str, int *c, t_flags *flags)
{
  int	count;

  count = -1;
  while (str[++count] != 0 && (flags->precision > 0 || flags->precision == -1))
    {
      if (str[count] >= 32 && str[count] < 127)
	my_putchar_printf(str[count], c);
      else
	{
	  my_putchar_printf('\\', c);
	  my_putchar_printf('0', c);
	  if (str[count] <= 7)
	    my_putchar_printf('0', c);
	  my_put_nbr_base(str[count], 8, flags, c);
	}
      if (flags->precision > 0)
	flags->precision -= 1;
    }
}

void	print_nbr(t_flags *flags, va_list ap, int *count)
{
  if (flags->format == 'o')
    display_number(flags, ap, "01234567", count);
  else if (flags->format == 'x' || flags->format == 'X')
    display_number(flags, ap, (flags->format == 'x' ?
			       "0123456789abcdef" : "0123456789ABCDEF"), count);
  else if (flags->format == 'b')
    display_number(flags, ap, "01", count);
  else if (flags->format == 'u')
    {
      flags->precision = -1;
      my_putstr_printf(my_unsigned_to_char(va_arg(ap, unsigned int)),
		       count, flags, 1);
    }
  else if (flags->format == 'p')
    display_pointer(flags, ap, count);
  else if (flags->length == 'l' && (flags->format == 'd' ||
				    flags->format == 'i'))
    my_putstr_printf(my_long_to_char(va_arg(ap, long)), count, flags, 1);
  else if (flags->format == 'd' || flags->format == 'i')
    display_number(flags, ap, "0123456789", count);
}

void	print_flag(t_flags *flags, va_list ap, int *count)
{
  if (flags->format == 's')
    my_putstr_printf(va_arg(ap, char *), count, flags, 0);
  else if (flags->format == 'S')
    my_octal_putstr(va_arg(ap, char *), count, flags);
  else if (flags->format == 'c')
	  my_putchar_printf(va_arg(ap, int), count);
  else if (flags->format == '%')
    my_putchar_printf('%', count);
}

void	initialize_flags(t_flags *flags, int *count)
{
  *count = 0;
  flags->width = 0;
  flags->precision = 0;
  flags->length = 0;
  flags->format = 0;
  flags->hold = 0;
}

int		my_printf(char *str, ...)
{
  int		count;
  va_list	ap;
  t_flags	flags;

  initialize_flags(&flags, &count);
  va_start(ap, str);
  while (*str != 0)
  {
    if (*str == '%')
    {
      flags.backup = str;
      str = get_flags(str + 1, &flags, ap, &count);
      if (flags.format == 'd' || flags.format == 'i' ||
	  flags.format == 'p' || flags.format == 'X' || flags.format == 'x' ||
	  flags.format == 'o' || flags.format == 'u' || flags.format == 'b')
	print_nbr(&flags, ap, &count);
      else
	print_flag(&flags, ap, &count);
    }
    else
      my_putchar_printf(*str, &count);
    str += 1;
  }
  va_end(ap);
  return (count);
}
