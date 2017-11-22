/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 15:13:03 by hleber            #+#    #+#             */
/*   Updated: 2015/06/11 18:11:54 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expertsystem.h"

static void	ft_init_env(t_env *env)
{
	env->lrules = NULL;
	env->lfacts = NULL;
	env->initfacts = NULL;
	env->questions = NULL;
	env->finish = TRUE;
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

static void	ft_display_initfacts(t_env *env)
{
	t_list	*lfacts;
	t_facts	*fact;

	lfacts = env->lfacts;
	ft_printf("Initials facts :\n");
	while (lfacts != NULL)
	{
		fact = lfacts->content;
		ft_printf("\033[1;34;40m%c\033[0m is ", fact->name);
		if (fact->status == FALSE)
			ft_printf("\033[1;31;40mFalse\033[0m\n");
		else if (fact->status == TRUE)
			ft_printf("\033[1;32;40mTrue\033[0m\n");
		else if (fact->status == UNDETER)
			ft_printf("\033[1;37;41mUndeterminable\033[0m\n");
		else if (fact->status == DETER)
			ft_printf("\033[1;33;40mDeterminable\033[0m\n");
		lfacts = lfacts->next;
	}
}

int			main(int ac, char **av)
{
	t_env	env;
	int		fd;

	if (ac != 2)
	{
		ft_putstr("usage : ./expert-system test/file.txt\n");
		exit (0);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		ft_perror_exit("Open File:");
	ft_init_env(&env);
	parse_arg(&env, fd);
	ft_display_initfacts(&env);
	ft_printf("\n\033[1;34;40mQuestion : %s\033[0m\n\n", env.questions);
	if (close(fd) == -1)
		ft_perror_exit("Close File:");
	ft_backward_chaining(&env);
	ft_printf("\n\033[1;34;40mSo %s is \033[0m", env.questions);
	if (env.finish == FALSE)
		ft_printf("\033[1;31;40mFalse\033[0m\n");
	else if (env.finish == TRUE)
		ft_printf("\033[1;32;40mTrue\033[0m\n");
	else if (env.finish == UNDETER)
		ft_printf("\033[1;37;41mUndeterminable\033[0m\n");
	return (0);
}
