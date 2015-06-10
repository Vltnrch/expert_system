/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expertsystem.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 15:15:04 by hleber            #+#    #+#             */
/*   Updated: 2015/06/10 19:06:32 by vroche           ###   ########.fr       */
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

typedef struct	s_env
{
	t_list		*lrules;
	t_list		*lfacts;
	char		*questions;
	char		*initfacts;
}				t_env;

typedef struct	s_expsys
{
	int			flag;
	char		*str;
}				t_expsys;

int				get_next_line(int const fd, char **line);
int				check_operator(t_expsys *exsy, int i);
int				check_operand(t_expsys *exsy, int i);
int				check_equal(t_expsys *exsy, int i);
int				check_imp(t_expsys *exsy, int i);
int				check_bracket(t_expsys *exsy, int i);
int				check_par(t_expsys *exsy);
int				valid_rules(t_expsys *exsy);
int				valid_file(t_expsys *exsy);
void			del_isspace(t_expsys *exsy);
int				valid_rules2(t_expsys *exsy, int i);
int				check_point(t_expsys *exsy, int i);
int				check_facts(t_expsys *exsy, int i);

void			ft_add_rules(t_env *env, char *before, char *after);
void			ft_add_facts(t_env *env, char name, int status);
int				ft_fact_isexist(t_env *env, char name);
int				ft_getstatus_fact(t_env *env, char name);
void			ft_changestatus_fact(t_env *env, char name, int status);
int				ft_fact_isinsearch(t_env *env, char name);
void			ft_changeinsearch_fact(t_env *env, char name, int insearch);

void			ft_backward_chaining(t_env *env);
int				ft_engine(t_env *env, char name);

int				ft_ultimate_check(t_env *env);

int				ft_check_char(char *s1, char *s2);

#endif
