/*
** solver.h for solver.h in /home/cedric/Desktop/solver
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sat Apr 29 13:48:34 2017 
** Last update Sun Apr 30 16:31:46 2017 
*/
#ifndef SOLVER_H_
# define SOLVER_H_

# define EPSILON	1.0e-10

typedef struct		s_poly
{
  int			nb;
  float			*poly;
}			t_poly;

typedef struct		s_solus
{
  int			nb;
  float			*solus;
}			t_solus;

/*
**caster.c
*/
t_solus		*init_solus();
void		del_solus(t_solus *my_solus);
int		solus_add(t_solus *my_solus, float solus);
void		del_polys(t_poly *my_poly);
t_poly		*create_poly(int size, ...);

/*
**solver.c
*/
t_solus		*solver(t_poly *poly);
float		get_min_pos_solus(t_solus *solus);

/*
**SEC
*/
t_solus		*solver_sec(float *poly);

/*
**THIRD
*/
t_solus		*solver_three(float *poly);

/*
**FOURTH
*/
t_solus         *solver_four(float *poly);
int		solver_four_part2(float *var, float *nxvar, t_solus *solus);
int		solver_four_part1(float *var, float *nxvar, t_solus *solus);

#endif /* !SOLVER_H_ */
