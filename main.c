/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 15:13:03 by hleber            #+#    #+#             */
/*   Updated: 2015/06/11 14:37:40 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

static void	ft_init_env(t_env *env)
{
	env->lrules = NULL;
	env->lfacts = NULL;
	env->initfacts = NULL;
	env->questions = NULL;
}

static void parse_arg_part(t_env *env, t_expsys *exsy)
{
	if (valid_file(exsy) == 0)
		ft_perror_exit("File:");
	if (valid_rules(exsy) == 0)
		ft_perror_exit("Rules:");
	if (check_par(exsy) != 0)
		ft_perror_exit("Rules Bracket:");
	if (*(exsy->str) != 0)
	{
		if (*(exsy->str) != '=' && *(exsy->str) != '?')
			ft_cut_rules(env, exsy);
		else if (*(exsy->str) == '=')
		{
			if (env->initfacts != NULL)
				ft_perror_exit("Multiple initial facts lines:");
			env->initfacts = ft_strdup(exsy->str + 1);
		}
		else if (*(exsy->str) == '?')
		{
			if (env->questions != NULL)
				ft_perror_exit("Multiple questions lines:");
			env->questions = ft_strdup(exsy->str + 1);
		}
	}
}

static void	parse_arg(t_env *env, int fd)
{
	t_expsys	exsy;
	char		*buf;

	exsy.str = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		exsy.str = buf;
		del_isspace(&exsy);
		parse_arg_part(env, &exsy);
		free(buf);
	}
	if (env->initfacts == NULL)
		ft_perror_exit("Where is initial facts ?! (=[...]):");
	if (env->questions == NULL || *(env->questions) == 0)
		ft_perror_exit("Where is the question ?! (?...):");
	if (env->lrules == NULL)
		ft_perror_exit("Where is the rules ?!:");
	if ((ft_check_no_multi_rules(env) == 0) || (check_same_char(env) == 0))
		ft_perror_exit("Rules:");
	ft_createlist_facts(env);
	ft_init_facts(env);
}

int			main(int ac, char **av)
{
	t_env	env;
	int		fd;
	t_facts	*fact;
	t_list	*lfacts;

	if (ac != 2)
	{
		ft_putstr("usage : ./expert-system test/file.txt\n");
		exit (0);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		ft_perror_exit("Open File:");
	ft_init_env(&env);
	parse_arg(&env, fd);
	lfacts = env.lfacts;
	while (lfacts != NULL)
	{
		fact = lfacts->content;
		printf("Name : %c || Status : %d\n", fact->name, fact->status);
		lfacts = lfacts->next;
	}
	printf("Question : %s\n", env.questions);
	if (close(fd) == -1)
		ft_perror_exit("Close File:");
	ft_backward_chaining(&env);
	return (0);
}
