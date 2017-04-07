/*
** inter.h for math.h in /home/cedric/delivery/MUL/raytracer2/libs
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Apr  4 21:29:16 2017 
** Last update Tue Apr  4 23:20:40 2017 
*/

#ifndef INTER_H_
# define INTER_H_

# define PRECISION	12
# define SECUR		500
# define POLY_MAX	5

typedef struct		s_poly
{
  int			elem;
  int			coef[POLY_MAX];
}			t_poly;

#endif /* !INTER_H_ */
