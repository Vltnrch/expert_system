/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expertsystem.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 15:15:04 by hleber            #+#    #+#             */
/*   Updated: 2015/06/11 14:42:52 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPERTSYSTEM_H
# define EXPERTSYSTEM_H

# include "libft.h"
# include <signal.h>
# include <fcntl.h>

# define FALSE 0
# define TRUE 1
# define UNDETER 2
# define DETER 3

# include <stdio.h>

typedef struct	s_rules
{
	char		*before;
	char		*after;
}				t_rules;

typedef struct	s_facts
{
	char		name;
	int			status;
	int			insearch;
}				t_facts;

typedef struct	s_expsys
{
	int			flag;
	char		*str;
}				t_expsys;

typedef struct	s_calc
{
	const char	*calcul;
	int			*left_dl;
	char		*op_dl;
	int			prio_op_pre;
	const char	**p_calcul;
	int			left;
	int			right;
	char		op;
	char		op_next;
	int			reverse;
}				t_calc;

typedef struct	s_env
{
	t_list		*lrules;
	t_list		*lfacts;
	char		*questions;
	char		*initfacts;
	t_calc		*work;
}				t_env;

int				check_operator(t_expsys *exsy, int i);
int				check_operand(t_expsys *exsy, int i);
int				check_equal(t_expsys *exsy, int i);
int				check_imp(t_expsys *exsy, int i);
int				check_bracket(t_expsys *exsy, int i);

int				check_par(t_expsys *exsy);
int				check_facts(t_expsys *exsy, int i);
int				check_point(t_expsys *exsy, int i);
int				valid_file(t_expsys *exsy);

float			add_ascii(char *s1);
int				ft_check_char(char *s1, char *s2);
int				check_same_char(t_env *env);

int				ft_check_no_multi_rules(t_env *env);

int				valid_rules(t_expsys *exsy);
int				valid_rules2(t_expsys *exsy, int i);

void			del_isspace(t_expsys *exsy);

int				ft_calc_rule(t_env *env, t_calc *calc);

void			ft_backward_chaining(t_env *env);
int				ft_engine(t_env *env, char name);

void			ft_add_rules(t_env *env, char *before, char *after);
void			ft_add_facts(t_env *env, char name, int status);
int				ft_fact_isexist(t_env *env, char name);
int				ft_fact_isinsearch(t_env *env, char name);

int				ft_getstatus_fact(t_env *env, char name);
void			ft_changestatus_fact(t_env *env, char name, int status);
void			ft_changeinsearch_fact(t_env *env, char name, int insearch);

void			ft_cut_rules(t_env *env, t_expsys *exsy);
void			ft_createlist_facts(t_env *env);
void			ft_init_facts(t_env *env);
void			ft_perror_exit(const char *str);

int				ft_check_char(char *s1, char *s2);

int				ft_do_op(int left, char op, int right);
int				ft_priority_op(char op);
int				ft_isop(char op);

#endif
