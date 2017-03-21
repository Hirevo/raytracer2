/*
** my_swap.c for my_swap in /home/nicolas.polomack/CPool_Day04
** 
** Made by Nicolas POLOMACK
** Login   <nicolas.polomack@epitech.net>
** 
** Started on  Thu Oct  6 09:03:28 2016 Nicolas POLOMACK
** Last update Thu Oct  6 09:42:12 2016 Nicolas POLOMACK
*/

int	my_swap(int *a, int *b)
{
  int	temp;

  temp = *a;
  *a = *b;
  *b = temp;
}
