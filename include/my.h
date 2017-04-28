/*
** my.h for my in /home/nicolas.polomack/CPool_Day09
**
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
**
** Started on  Thu Oct 13 10:04:36 2016 Nicolas POLOMACK
** Last update Mon Apr 24 13:02:59 2017 Nicolas Polomack
*/

#ifndef MY_H_
# define MY_H_

# include <stdarg.h>

typedef struct	s_flags
{
  char		format;
  char		length;
  char		hold;
  int		width;
  int		precision;
  char		*backup;
} 		t_flags;

int	my_puterror(char *);
void	my_putchar(char);
void	my_memcpy(void *, void *, int);
char	*my_memset(char *, char, int);
void	my_mset(void *, int, int);
int	my_isneg(int);
void	my_put_nbr(int);
int	my_swap(int, int);
void	my_putstr(char *);
int	my_strlen(char *);
int	my_getnbr(char *);
int	*my_sort_int_tab(int *, int);
int	my_power_rec(int, int);
int	my_square_root(int);
int	my_is_prime(int);
int	my_find_prime_sup(int);
char	*my_strcpy(char *, char *);
char	*my_strncpy(char *, char *, int);
char	*my_revstr(char *);
char	*my_strstr(char *, char*);
int	my_strcmp(const char *, const char*);
int	my_strncmp(const char *, const char *, int);
char	*my_strupcase(char *);
char	*my_strlowcase(char *);
char	*my_strcapitalize(char *);
int	my_str_isalpha(char *);
int	my_str_isnum(char *);
int	my_str_islower(char *);
int	my_str_isupper(char *);
int	my_str_isprintable(char *);
int	my_showstr(char *);
int	my_showmem(char *, int);
char	*my_strcat(char *, char *);
char	*my_strncat(char *, char *, int);
char	*my_strdup(char *);
char	*my_strndup(char *, int);
void	my_display2(double, int, int, int);
void	my_loop(double, int, int, int);
int	my_compare1(char *, char *);
int	my_compare(char *, char *, int);
int	my_printf(char *, ...);
void	print_flag(t_flags *, va_list, int *);
t_flags	*inititalize_flags(t_flags **, int *);
char	*get_flags(char *, t_flags *, va_list, int *);
void	my_octal_putstr(char *, int *, t_flags *);
void	my_put_nbr_base(int, int, t_flags *, int *);
void	my_put_nbr_long(long, int *);
void	my_put_nbr_unsigned(unsigned int, int *);
void	my_putchar_printf(char, int *);
void	my_putstr_printf(char *, int *, t_flags *, int);
char	*my_int_to_char(int);
char	*my_unsigned_to_char(unsigned int);
char	*my_long_to_char(long);
void	display_pointer(t_flags *, va_list, int *);
void	display_number(t_flags *, va_list, char *, int *);
char	*complete_str(char *, t_flags *, int *, int);
char	*convert_base(char *, char *, char *);
char	*check_parse(char *, t_flags *, int *);

#endif /* !MY_H_ */
